#include <3dstris/states/menu/loadfailed.hpp>
#include <3dstris/states/menu/mainmenu.hpp>

int main() {
	// Services are not (de)initialized here; instead, Game does graphics
	// initialization, while Config does RomFS (de)init

	// The reason for this is that BaseSettings::config (a static variable) is
	// initialized as a copy of Game::get().getConfig(), a method which, after
	// being called to initialize a static variable, calls the Game and Config
	// constructor *before* the main function is called

	// These constructors attempt to use the romfs service and various others,
	// however none are initialized at the time of construction,
	// therefore making it impossible to initialize said services here

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
