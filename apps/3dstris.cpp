#include <citro2d.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <3dstris/state.hpp>
#include <3dstris/game.hpp>
#include <3dstris/states/mainmenu.hpp>

int main() {
	srand(u32(osGetTime()));

	TickCounter tickCounter;
	osTickCounterStart(&tickCounter);

	// Init libs
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();

	Game game = Game();
	game.setState(new MainMenu(game));

	while (aptMainLoop() && !game.exit) {
		hidScanInput();

		osTickCounterUpdate(&tickCounter);
		double dt = osTickCounterRead(&tickCounter) / 1000;

		game.update(dt);

		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

		game.draw();

		C3D_FrameEnd(0);
	}

	// Deinit libs
	C2D_Fini();
	C3D_Fini();
	gfxExit();
}