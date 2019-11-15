#include <3dstris/board.hpp>
#include <3dstris/piece.hpp>

// Ching cong
Piece::Piece(Board& board, PieceShape shape, PieceType type) : board(board) {
	reset(shape, type);
}

void Piece::reset(PieceShape shape, PieceType type) {
	this->shape = shape;
	this->type = type;
	color = colors[type];
	ghostColor = colorsGhost[type];
	size = std::sqrt(shape.size());
	pos = {std::floor(board.width / 2.f) - std::floor(size / 2.f), 0};
	fallTimer = 0.0f;
	hasSet = false;
	das = 0.2f;	 //0.138f;
	dasTimer = {0.0f, 0.0f};
	arr = 0.0f;
	arrTimer = arr;
}

void Piece::set() {
	for (int y = 0; y < size; ++y) {
		for (int x = 0; x < size; ++x) {
			if (shape[y * size + x]) {
				board.set(pos.x + x, pos.y + y, type);
			}
		}
	}
	board.clearLines();
}

bool Piece::collides(int offX, int offY) {
	for (int y = 0; y < size; ++y) {
		for (int x = 0; x < size; ++x) {
			Vector2 offPos = {pos.x + x + offX, pos.y + y + offY};
			if (shape[y * size + x] && (!board.inside(offPos) ||
										board.get(offPos) != PieceType::None)) {
				return true;
			}
		}
	}
	return false;
}

void Piece::draw(Vector2 origin, int tileSize) {
	int ghostY = 0;
	while (!collides(0, ghostY++)) {
	}
	ghostY -= 2;

	for (int y = 0; y < size; ++y) {
		for (int x = 0; x < size; ++x) {
			if (shape[y * size + x]) {
				C2D_DrawRectSolid(origin.x + (pos.x + x) * tileSize,
								  origin.y + (pos.y + y) * tileSize, 0.0f,
								  tileSize, tileSize, color);
				C2D_DrawRectSolid(origin.x + (pos.x + x) * tileSize,
								  origin.y + (pos.y + ghostY + y) * tileSize,
								  0.0f, tileSize, tileSize, ghostColor);
			}
		}
	}
}

void Piece::draw(Vector2 origin, int tileSize, PieceShape& shape, Color color) {
	const int size = std::sqrt(shape.size());
	for (int y = 0; y < size; ++y) {
		for (int x = 0; x < size; ++x) {
			if (shape[y * size + x]) {
				C2D_DrawRectSolid(origin.x + x * tileSize,
								  origin.y + y * tileSize, 0.0f, tileSize,
								  tileSize, color);
			}
		}
	}
}

bool Piece::move(Direction dir) {
	float xOff = 0, yOff = 0;
	switch (dir) {
		case Direction::left:
			xOff = -1;
			break;
		case Direction::right:
			xOff = 1;
			break;
		case Direction::up:
			yOff = -1;
			break;
		case Direction::down:
			yOff = 1;
			break;
	}
	if (!collides(xOff, yOff)) {
		pos.x += xOff;
		pos.y += yOff;
		return true;
	}
	return false;
}

void Piece::rotate(bool ccw) {
	PieceShape newShape;
	newShape.resize(size * size, false);
	for (int y = 0; y < size; ++y) {
		for (int x = 0; x < size; ++x) {
			if (shape[y * size + x]) {
				if (ccw) {
					newShape[(size - x - 1) * size + y] = true;
				} else {
					newShape[x * size + size - y - 1] = true;
				}
			}
		}
	}
	shape = newShape;
}

void Piece::update(float dt, u32 kDown, u32 kHeld) {
	fallTimer += dt;
	if (fallTimer > 1.0f) {
		fallTimer = 0.0f;
		move(Direction::down);
	}

	if (kDown & KEY_UP) {
		while (move(Direction::down)) {
		}
		hasSet = true;
		set();
		return;
	}

	dasTimer.x = kHeld & KEY_LEFT ? dasTimer.x + dt : 0.0f;
	dasTimer.y = kHeld & KEY_RIGHT ? dasTimer.y + dt : 0.0f;

	bool moved = false;

	if (dasTimer.x > das) {
		if (arr == 0.0f) {
			while (move(Direction::left)) {
			}
		} else {
			arrTimer -= dt;
			if (arrTimer <= 0.0f) {
				move(Direction::left);
				arrTimer = arr;
			}
		}
		moved = true;
	} else if (kDown & KEY_LEFT) {
		move(Direction::left);
		arrTimer = arr;
		moved = true;
	}

	if (dasTimer.y > das && !moved) {
		if (arr == 0.0f) {
			while (move(Direction::right)) {
			}
		} else {
			arrTimer -= dt;
			if (arrTimer <= 0.0f) {
				move(Direction::right);
				arrTimer = arr;
			}
		}
	} else if (kDown & KEY_RIGHT) {
		move(Direction::right);
		arrTimer = arr;
	}

	if (kDown & KEY_Y)
		rotate(true);
	if (kDown & KEY_B)
		rotate(false);
}