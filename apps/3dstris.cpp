#include <tex3ds.h>
#include <3dstris/game.hpp>
#include <3dstris/state.hpp>
#include <3dstris/states/configfailed.hpp>
#include <3dstris/states/configscreen.hpp>
#include <3dstris/states/mainmenu.hpp>

int main() {
	TickCounter tickCounter;
	osTickCounterStart(&tickCounter);

	// Init libs
	gfxInitDefault();
	romfsInit();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();

	Game& game = Game::getInstance();
	if (!Game::getInstance().getConfig().configFailed) {
		game.setState(make_unique<ConfigScreen>());
	} else {
		game.setState(make_unique<ConfigFailed>());
	}

	while (aptMainLoop() && !game.exit) {
		hidScanInput();

		osTickCounterUpdate(&tickCounter);

		game.update(osTickCounterRead(&tickCounter) / 1000);

		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		game.draw();
		C3D_FrameEnd(0);
	}

	// Deinit libs
	C2D_Fini();
	C3D_Fini();
	gfxExit();
}
