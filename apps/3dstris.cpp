#include <3dstris/states/menu/configscreen.hpp>
#include <3dstris/states/menu/loadfailed.hpp>
#include <3dstris/states/menu/mainmenu.hpp>

int main() {
	TickCounter tickCounter;
	osTickCounterStart(&tickCounter);

	gfxInitDefault();
	romfsInit();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();

	Game& game = Game::get();
	game.pushState(make_unique<MainMenu>());
	if (game.getConfig().failed()) {
		game.pushState(make_unique<LoadFailed>());
	}
	if (game.getGames().failed()) {
		game.pushState(make_unique<LoadFailed>(LoadFailed::GAMES));
	}
	if (game.getKeybinds().failed()) {
		game.pushState(make_unique<LoadFailed>(LoadFailed::KEYBINDS));
	}

	while (aptMainLoop() && !game.exit) {
		hidScanInput();

		osTickCounterUpdate(&tickCounter);

		game.update(osTickCounterRead(&tickCounter) / 1000);

		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		game.draw();
		C3D_FrameEnd(0);
	}

	C2D_Fini();
	C3D_Fini();
	gfxExit();
}
