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

	TickCounter tickCounter;
	osTickCounterStart(&tickCounter);

	// Init libs
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	consoleInit(GFX_BOTTOM, nullptr);

	char* version_text = static_cast<char*>(
		malloc(1 + strlen(_3DSTRIS_VERSION) + strlen(_3DSTRIS_GIT_HASH)));
	sprintf(version_text, "v%s-%s", _3DSTRIS_VERSION, _3DSTRIS_GIT_HASH);

	C2D_Text version;
	C2D_TextParse(&version, text_buf, version_text);
	C2D_TextOptimize(&version);

	std::mt19937 bagRNG(static_cast<u32>(rand()));

	// Create screens
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

	Color bg_color = C2D_Color32(34, 34, 34, 255);

	Board board = Board(10, 20);

	const u32 tileSize = (SCREEN_HEIGHT - 10) / board.height;

	Vector2 origin = {
		SCREEN_WIDTH / 2.0f - (board.width / 2.0f) * float(tileSize), 10.0f};

	// bag
	const int upcoming = 5;
	const auto _bag = genBag(bagRNG);
	std::deque<PieceType> bag(_bag.begin(), _bag.end());

	Piece piece = Piece(board, bag.front());
	bag.pop_front();

	PieceType hold = PieceType::None;
	bool hasHeld = false;

	while (aptMainLoop()) {
		hidScanInput();

		u32 kDown = hidKeysDown();
		u32 kHeld = hidKeysHeld();
		if (kDown & KEY_START) {
			break;	// goes back to hb menu
		}

		osTickCounterUpdate(&tickCounter);
		double deltaTime = osTickCounterRead(&tickCounter) / 1000;
		piece.update(deltaTime, kDown, kHeld);

		if (piece.hasSet()) {
			hasHeld = false;
			piece.reset(bag.front());
			bag.pop_front();
			if (bag.size() < upcoming) {
				for (const auto& p : genBag(bagRNG)) {
					bag.push_back(p);
				}
			}
		}

		if (!hasHeld && (kDown & KEY_X || kDown & KEY_A)) {
			hasHeld = true;
			if (hold == PieceType::None) {
				hold = piece.getType();
				piece.reset(bag.front());
				bag.pop_front();
			} else {
				PieceType tmp = piece.getType();
				piece.reset(hold);
				hold = tmp;
			}
		}

		// Render the scene
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, bg_color);
		C2D_SceneBegin(top);

		board.draw(origin, tileSize);
		piece.draw(origin, tileSize);

		// draw bag
		u32 y = 1;
		for (u32 i = 0; i < upcoming; ++i) {
			const auto& p = bag[i];
			if (p == PieceType::I) --y;
			Piece::draw({origin.x + (board.width + 1 + (p == PieceType::O ? 1 : 0)) * tileSize,
						 origin.y + y * tileSize},
						tileSize, shapes[p], colors[p]);
			y += shapes[p].size;
			if (p == PieceType::O) ++y;
		}

		// draw held piece
		if (hold != PieceType::None) {
			Piece::draw(
				{origin.x - (shapes[hold].size + 1) * tileSize, origin.y + tileSize},
				tileSize, shapes[hold], colors[hold]);
		}

		// draw version
		C2D_DrawText(&version, C2D_WithColor, 1, 0, 0.5f, 0.5f, 0.5f,
					 Colors::I);

		C3D_FrameEnd(0);
	}

	// Deinit libs
	C2D_Fini();
	C3D_Fini();
	gfxExit();
}