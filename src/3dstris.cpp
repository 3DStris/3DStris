#include <3dstris/states/menu/loadfailed.hpp>
#include <3dstris/states/menu/mainmenu.hpp>
#include <3dstris/util/log.hpp>

int main() {
	// Services are not initialized here; instead, Game does graphics
	// initialization, while Config does RomFS initialization
	// The reason for this is BaseSettings::config, which is a static variable,
	// initialized as a copy of Game::get().getConfig(), which in turn calls the
	// Game and Config constructor before the main function is called

#ifndef NDEBUG
	consoleDebugInit(debugDevice_3DMOO);
	Log::get().setLevel(Log::Level::DEBUG);
	Log::get().setQuiet(false);
#endif

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
