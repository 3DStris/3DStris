#include <citro2d.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <3dstris/board.hpp>
#include <3dstris/shapes.hpp>
#include <3dstris/version.hpp>
#include <algorithm>
#include <array>
#include <cmath>
#include <deque>
#include <random>

std::array<PieceType, 7> genBag(std::mt19937& rng) {
	std::array<PieceType, 7> pieces{PieceType::I, PieceType::O, PieceType::L,
									PieceType::J, PieceType::S, PieceType::T,
									PieceType::Z};
	std::shuffle(pieces.begin(), pieces.end(), rng);
	return pieces;
}

int main() {
	srand(u32(osGetTime()));

	// Init libs
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	consoleInit(GFX_BOTTOM, nullptr);

	char* version_text =
		static_cast<char*>(malloc(1 + strlen(_3DSTRIS_VERSION)));
	sprintf(version_text, "v%s", _3DSTRIS_VERSION);

	C2D_Text version;
	C2D_TextParse(&version, text_buf, version_text);
	C2D_TextOptimize(&version);

	std::mt19937 bagRNG(static_cast<u32>(rand()));

	// Create screens
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

	Color bg_color = C2D_Color32(34, 34, 34, 255);

	Board board = Board(10, 20);

	const u32 tileSize = (SCREEN_HEIGHT - 10) / board.height;

	Vector2 origin = {SCREEN_WIDTH / 2.0f -
						  (board.width / 2.0f) * static_cast<float>(tileSize),
					  10.0f};

	// bag
	const int min_bag = 4;
	std::deque<PieceType> bag;
	for (const auto& p : genBag(bagRNG)) {
		bag.push_back(p);
	}

	Piece piece = Piece(board, shapes[bag.front()], bag.front());
	bag.pop_front();

	float dt =
		1.0f / 60.0f;  // hardcoded because im too lazy to use std::chrono
	while (aptMainLoop()) {
		hidScanInput();

		u32 kDown = hidKeysDown();
		u32 kHeld = hidKeysHeld();
		if (kDown & KEY_START) {
			break;	// goes back to hb menu
		}

		piece.update(dt, kDown, kHeld);

		if (piece.hasSet()) {
			piece.reset(shapes[bag.front()], bag.front());
			bag.pop_front();
			if (bag.size() < min_bag) {
				for (const auto& p : genBag(bagRNG)) {
					bag.push_back(p);
				}
			}
		}

		// Render the scene
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, bg_color);
		C2D_SceneBegin(top);

		board.draw(origin, tileSize);
		piece.draw(origin, tileSize);

		// draw bag
		int y = 0;
		for (PieceType p : bag) {
			Piece::draw({origin.x + board.width * tileSize + 30,
						 origin.y + y * tileSize},
						tileSize, shapes[p], colors[p]);
			y += int(std::sqrt(shapes[p].size()) + 1);
		}

		C2D_DrawText(&version, C2D_WithColor, 1, 0, 0.5f, 0.5f, 0.5f,
					 Colors::I);

		C3D_FrameEnd(0);
	}

	// Deinit libs
	C2D_Fini();
	C3D_Fini();
	gfxExit();
}