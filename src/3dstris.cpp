#include <3dstris/states/menu/loadfailed.hpp>
#include <3dstris/states/menu/mainmenu.hpp>

int main() {
	// Services are not (de)initialized here; instead, Game does graphics
	// de(init), while Config does RomFS (de)init

	// The reason for this is that BaseSettings::config (a static variable) is
	// initialized as a copy of Game::get().getConfig(), a method which, after
	// being called to initialize a static variable, calls the Game and Config
	// constructor *before* the main function is called, whicn in turn call
	// various services which, if initialized here, are not initialized at the
	// time of construction

	Game& game = Game::get();
	game.pushState(make_unique<MainMenu>());
	if (game.getConfig().failed()) {
		game.pushState(make_unique<LoadFailed>());
	}
	if (game.getGames().failed()) {
		game.pushState(make_unique<LoadFailed>(LoadFailed::FailType::GAMES));
	}
	if (game.getKeybinds().failed()) {
		game.pushState(make_unique<LoadFailed>(LoadFailed::FailType::KEYBINDS));
	}

	TickCounter tickCounter;
	osTickCounterStart(&tickCounter);
	while (aptMainLoop() && !game.exit) {
		hidScanInput();

		osTickCounterUpdate(&tickCounter);

		game.update(osTickCounterRead(&tickCounter) / 1000);

		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		game.draw();
		C3D_FrameEnd(0);
	}

	game.getGames().joinLoadThread();
	game.getGames().joinSaveThread();
}
