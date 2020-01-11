#include <3dstris/board.hpp>

Board::Board(u32 width, u32 height) : width(width), height(height) {
	reset();
}

void Board::reset() {
	_linesCleared = 0;
	grid.assign(width * height, PieceType::None);
}

bool Board::inside(u32 x, u32 y) {
	return x < width && y < height;
}
bool Board::inside(int x, int y) {
	return x >= 0 && y >= 0 &&  //
		   inside(u32(x), u32(y));
}
bool Board::inside(Vector2 pos) {
	return inside(int(pos.x), int(pos.y));
}

void Board::set(u32 x, u32 y, PieceType t) {
	if (inside(x, y)) {
		grid[y * width + x] = t;
	}
}
void Board::set(int x, int y, PieceType t) {
	if (inside(x, y)) {
		set(u32(x), u32(y), t);
	}
}
void Board::set(Vector2 pos, PieceType t) {
	set(u32(pos.x), u32(pos.y), t);
}

PieceType Board::get(u32 x, u32 y) const {
	return grid[y * width + x];
}
PieceType Board::get(Vector2 pos) const {
	return get(u32(pos.x), u32(pos.y));
}

void Board::draw(Vector2 origin, u32 tileSize, int outerThick,
				 int gridThick) const {
	// top
	straightLine(origin.x, origin.y, width * tileSize, 0, outerThick, BLACK);
	// bottom
	straightLine(origin.x, origin.y + height * tileSize, width * tileSize, 0,
				 outerThick, BLACK);
	// left
	straightLine(origin.x, origin.y, 0, height * tileSize, outerThick, BLACK);
	// right
	straightLine(origin.x + width * tileSize, origin.y, 0, height * tileSize,
				 outerThick, BLACK);

	for (u32 y = 1; y < height; ++y) {
		straightLine(origin.x, origin.y + y * tileSize, width * tileSize, 0,
					 gridThick, GRIDBLACK);
	}
	for (u32 x = 1; x < width; ++x) {
		straightLine(origin.x + x * tileSize, origin.y, 0.0f, height * tileSize,
					 gridThick, GRIDBLACK);
	}

	for (u32 y = 0; y < height; ++y) {
		for (u32 x = 0; x < width; ++x) {
			const PieceType& p = get(x, y);
			if (p != PieceType::None) {
				C2D_DrawRectSolid(origin.x + x * tileSize,
								  origin.y + y * tileSize, 0.0f, tileSize,
								  tileSize, colors[p]);
			}
		}
	}
}

void Board::clearLines() {
	for (u32 y = 0; y < height; ++y) {
		bool line = true;
		for (u32 x = 0; x < width; ++x) {
			if (get(x, y) == PieceType::None) {
				line = false;
				break;
			}
		}
		if (line) {
			_linesCleared++;
			for (u32 curY = y; curY >= 1; --curY) {
				for (u32 x = 0; x < width; ++x) {
					set(x, curY,
						curY == 1 ? PieceType::None : get(x, curY - 1));
				}
			}
		}
	}
}
