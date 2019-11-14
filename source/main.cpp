#include <citro2d.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <array>

#include "board.hpp"
#include "shapes.hpp"

float randf() {
	return static_cast<float>(rand()) / RAND_MAX;
}

int main() {
	// Init libs
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	consoleInit(GFX_BOTTOM, NULL);

	// Create screens
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

	Color colBg = C2D_Color32(34, 34, 34, 255);

	const int tileSize = (SCREEN_HEIGHT - 10)/20;

	std::array<PieceType, 7> pieces{PieceType::I, PieceType::O, PieceType::L, PieceType::J, PieceType::S, PieceType::T, PieceType::Z};

	Board board = Board(10, 20);
	Vector2 origin = {SCREEN_WIDTH / 2.0f - (board.width / 2.0f) * static_cast<float>(tileSize), 10.0f};

	Piece piece = Piece(board, shapes[PieceType::I], PieceType::I);
	float dt = 1.0f / 60.0f; // hardcoded because im too lazy to use std::chrono
	while (aptMainLoop()) {
		hidScanInput();

		u32 kDown = hidKeysDown();
		u32 kHeld = hidKeysHeld();
		if (kDown & KEY_START) {
			break; // goes back to hb menu
		}

		piece.update(dt, kDown, kHeld);

		if (piece.hasSet) {
			PieceType p = pieces[static_cast<int>(randf() * pieces.size())];
			piece.reset(shapes[p], p);
		}
		
		// Render the scene
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, colBg);
		C2D_SceneBegin(top);

		board.draw(origin, tileSize);
		piece.draw(origin, tileSize);

		C3D_FrameEnd(0);
	}

	// Deinit libs
	C2D_Fini();
	C3D_Fini();
	gfxExit();
}