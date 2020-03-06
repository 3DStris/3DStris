#include <3dstris/game.hpp>
#include <3dstris/game/board.hpp>
#include <3dstris/gui.hpp>

Board::Board(const u32 width, const u32 height) : width(width), height(height) {
	grid.reserve(width * height);
	reset();
}

void Board::reset() {
	grid.assign(width * height, PieceType::NONE);

	_linesCleared = 0;
	_droppedPieces = 0;
}

void Board::draw(const Pos origin, const u32 tileSize, const float outerThick,
				 const float gridThick) const {
	GUI::drawOutline(Pos{origin.x, origin.y},
					 WH(width * tileSize, height * tileSize), outerThick, BOARD,
					 0.1f);

	for (u32 y = 0; y < height; ++y) {
		straightLine(Pos{origin.x, origin.y + y * tileSize},
					 WH(width * tileSize, 0), gridThick, GRID, 0);
	}
	for (u32 x = 0; x < width; ++x) {
		straightLine(Pos{origin.x + x * tileSize, origin.y},
					 WH(0, height * tileSize), gridThick, GRID, 0);
	}

	for (u32 y = 0; y < height; ++y) {
		for (u32 x = 0; x < width; ++x) {
			const PieceType p = get(x, y);

			if (p != PieceType::NONE && p != PieceType::INVALID) {
				const float pieceX = origin.x + x * tileSize;
				const float pieceY = origin.y + y * tileSize;
				if (Game::get().getConfig().useTextures) {
					C2D_DrawImageAt(Textures::get(static_cast<size_t>(p)),
									pieceX, pieceY, 0.5f);
				} else {
					C2D_DrawRectSolid(
						pieceX, pieceY, 0.5f, tileSize, tileSize,
						Textures::getColor(static_cast<size_t>(p)));
				}
			}
		}
	}
}

void Board::clearLines() {
	for (u32 y = 0; y < height; ++y) {
		bool line = true;
		for (u32 x = 0; x < width; ++x) {
			if (get(x, y) == PieceType::NONE) {
				line = false;
				break;
			}
		}

		if (line) {
			_linesCleared++;
			for (u32 curY = y; curY >= 1; --curY) {
				for (u32 x = 0; x < width; ++x) {
					set(x, curY,
						curY == 1 ? PieceType::NONE : get(x, curY - 1));
				}
			}
		}
	}
}
