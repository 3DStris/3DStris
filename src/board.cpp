#include <3dstris/board.hpp>
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

bool Board::inside(const Pos pos) const noexcept {
	return inside(int(pos.x), int(pos.y));
}

void Board::set(const Pos pos, const PieceType t) {
	set(pos.x, pos.y, t);
}

PieceType Board::get(const Pos pos) const {
	return get(pos.x, pos.y);
}

void Board::draw(const Vector2 origin, const u32 tileSize,
				 const float outerThick, const float gridThick) const {
	GUI::drawOutline(Pos{origin.x, origin.y},
					 WH{float(width * tileSize), float(height * tileSize)},
					 outerThick, BOARD, 0.1f);

	for (u32 y = 1; y < height; ++y) {
		straightLine(Pos{origin.x, origin.y + y * tileSize},
					 WH{float(width * tileSize), 0}, gridThick, GRID, 0);
	}
	for (u32 x = 1; x < width; ++x) {
		straightLine(Pos{origin.x + x * tileSize, origin.y},
					 WH{0, float(height * tileSize)}, gridThick, GRID, 0);
	}

	for (u32 y = 0; y < height; ++y) {
		for (u32 x = 0; x < width; ++x) {
			const PieceType p = get(x, y);

			if (p != NONE && p != INVALID) {
				const float pieceX = origin.x + x * tileSize;
				const float pieceY = origin.y + y * tileSize;
				if (Game::get().getConfig().useTextures) {
					C2D_DrawImageAt(Textures::get(p), pieceX, pieceY, 0.5f);
				} else {
					C2D_DrawRectSolid(pieceX, pieceY, 0.5f, tileSize, tileSize,
									  Textures::getColor(p));
				}
			}
		}
	}
}

void Board::clearLines() {
	for (u32 y = 0; y < height; ++y) {
		bool line = true;
		for (u32 x = 0; x < width; ++x) {
			if (get(x, y) == NONE) {
				line = false;
				break;
			}
		}

		if (line) {
			_linesCleared++;
			for (u32 curY = y; curY >= 1; --curY) {
				for (u32 x = 0; x < width; ++x) {
					set(x, curY, curY == 1 ? NONE : get(x, curY - 1));
				}
			}
		}
	}
}
