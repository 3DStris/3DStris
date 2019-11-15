#include <3dstris/board.hpp>

Board::Board(int width, int height) : width(width), height(height) {
	grid.resize(width * height, PieceType::None);
}

bool Board::inside(int x, int y) {
	return x >= 0 && x < width && y >= 0 && y < height;
}
bool Board::inside(Vector2 pos) {
	return inside(pos.x, pos.y);
}

void Board::set(int x, int y, PieceType t) {
	if (inside(x, y))
		grid[y * width + x] = t;
}
void Board::set(Vector2 pos, PieceType t) {
	set(pos.x, pos.y, t);
}

PieceType Board::get(int x, int y) {
	return grid[y * width + x];
}
PieceType Board::get(Vector2 pos) {
	return get(pos.x, pos.y);
}

void Board::draw(Vector2 origin, int tileSize) {
	const int outerThick = 2;
	// top
	straightLine(origin.x, origin.y, width * tileSize, 0.0f, outerThick, BLACK);
	// bottom
	straightLine(origin.x, origin.y + height * tileSize, width * tileSize, 0.0f,
				 outerThick, BLACK);
	// left
	straightLine(origin.x, origin.y, 0.0f, height * tileSize, outerThick,
				 BLACK);
	// right
	straightLine(origin.x + width * tileSize, origin.y, 0.0f, height * tileSize,
				 outerThick, BLACK);

	const int gridThick = 1;

	for (int y = 1; y < height; ++y) {
		straightLine(origin.x, origin.y + y * tileSize, width * tileSize, 0.0f,
					 gridThick, GRIDBLACK);
	}
	for (int x = 1; x < width; ++x) {
		straightLine(origin.x + x * tileSize, origin.y, 0.0f, height * tileSize,
					 gridThick, GRIDBLACK);
	}

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			PieceType p = get(x, y);
			if (p != PieceType::None) {
				C2D_DrawRectSolid(origin.x + x * tileSize,
								  origin.y + y * tileSize, 0.0f, tileSize,
								  tileSize, colors[p]);
			}
		}
	}
}

void Board::clearLines() {
	for (int y = 0; y < height; ++y) {
		bool line = true;
		for (int x = 0; x < width; ++x) {
			if (get(x, y) == PieceType::None) {
				line = false;
				break;
			}
		}
		if (line) {
			for (int curY = y; curY >= 1; --curY) {
				for (int x = 0; x < width; ++x) {
					set(x, curY,
						curY == 1 ? PieceType::None : get(x, curY - 1));
				}
			}
		}
	}
}