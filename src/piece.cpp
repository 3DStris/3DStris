#include <3dstris/board.hpp>
#include <3dstris/game.hpp>

// Ching cong
Piece::Piece(Board& board, const PieceShape& shape, const PieceType type)
	: board(board) {
	reset(shape, type);
}

Piece::Piece(Board& board, const PieceType type)
	: Piece(board, shapes[type], type) {
	// Uhh
}

void Piece::reset(const PieceShape& shape, const PieceType type) {
	this->shape = shape;
	this->type = type;

	pos = {std::floor(board.width / 2.0f) - std::floor(shape.size / 2.0f), 0};

	color = colors[type];
	ghostColor = colorsGhost[type];

	fallTimer = 0.0;
	fallAfter = 1.0;
	sDropAfter = 0.05;
	setTimer = 0.0;
	setAfter = 1.0;

	das = Game::getInstance().getConfig().das / 1000.;
	dasTimer = {0.0, 0.0};

	arr = Game::getInstance().getConfig().arr / 1000.;
	arrTimer = arr;

	rotation = 0;

	_dead =
		collides(0, 0);  // piece is "dead" if it collides as soon as it spawns
}

void Piece::reset(const PieceType type) {
	reset(shapes[type], type);
}

void Piece::set() {
	for (u32 y = 0; y < shape.size; ++y) {
		for (u32 x = 0; x < shape.size; ++x) {
			if (shape.shape[y * shape.size + x]) {
				board.set(u32(pos.x + x), u32(pos.y + y), type);
			}
		}
	}
	board.dropPiece();
	board.clearLines();
}

bool Piece::collides(const int offX, const int offY) const {
	for (u32 y = 0; y < shape.size; ++y) {
		for (u32 x = 0; x < shape.size; ++x) {
			Vector2 offPos = {pos.x + x + offX, pos.y + y + offY};
			if (shape.shape[y * shape.size + x] &&
				(!board.inside(offPos) ||
				 board.get(offPos) != PieceType::NONE)) {
				return true;
			}
		}
	}
	return false;
}

void Piece::draw(const Vector2 origin, const u32 tileSize) const {
	int ghostY = 0;
	while (!collides(0, ++ghostY)) {
	}
	ghostY--;

	for (u32 y = 0; y < shape.size; ++y) {
		for (u32 x = 0; x < shape.size; ++x) {
			if (shape.shape[y * shape.size + x]) {
				C2D_DrawRectSolid(origin.x + (pos.x + x) * tileSize,
								  origin.y + (pos.y + y) * tileSize, 0.5f,
								  tileSize, tileSize, color);
				C2D_DrawRectSolid(origin.x + (pos.x + x) * tileSize,
								  origin.y + (pos.y + ghostY + y) * tileSize,
								  0.5f, tileSize, tileSize, ghostColor);
			}
		}
	}
}

void Piece::draw(const Vector2 origin, const u32 tileSize,
				 const PieceShape& shape, const Color color) {
	for (u32 y = 0; y < shape.size; ++y) {
		for (u32 x = 0; x < shape.size; ++x) {
			if (shape.shape[y * shape.size + x]) {
				C2D_DrawRectSolid(origin.x + x * tileSize,
								  origin.y + y * tileSize, 0.5f, tileSize,
								  tileSize, color);
			}
		}
	}
}

bool Piece::move(const Direction dir) {
	int xOff = 0, yOff = 0;
	switch (dir) {
		case Direction::LEFT:
			xOff = -1;
			break;
		case Direction::RIGHT:
			xOff = 1;
			break;
		case Direction::UP:
			yOff = -1;
			break;
		case Direction::DOWN:
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

void Piece::rotate(const bool ccw) {
	if (type == PieceType::O)
		return;
	PieceShape newShape;
	newShape.shape.resize(shape.size * shape.size, false);
	newShape.size = shape.size;
	for (u32 y = 0; y < shape.size; ++y) {
		for (u32 x = 0; x < shape.size; ++x) {
			if (shape.shape[y * shape.size + x]) {
				if (ccw) {
					newShape.shape[(shape.size - x - 1) * shape.size + y] =
						true;
				} else {
					newShape.shape[x * shape.size + shape.size - y - 1] = true;
				}
			}
		}
	}
	PieceShape oldShape = shape;
	shape = newShape;

	int prevRotation = rotation;
	rotation = mod(rotation + (ccw ? -1 : 1), 4);

	Wallkick wkData = type == PieceType::I ? Wallkicks::I : Wallkicks::OTHERS;

	/*
	each test is stored as {spawn->ccw, spawn->cw, cw->spawn, cw->180, 180->cw,
	180->ccw, ccw->180, ccw->spawn} considering spawn = 0, cw = 1, 180 = 2, ccw
	= 3 (aka add one when rotating clockwise, remove when counter clockwise, and
	always mod 4) it becomes {0->3, 0->1, 1->0, 1->2, 2->1, 2->3, 3->2, 3->0}
	its in that order so that:
	[.., state->state after ccw, state->state after cw, ..]
	which makes it easy to index by using (ccw being true if the current
	rotation is counter clockwise) 2 * prevRotation + (ccw ? 0 : 1)
	*/

	int testOffset = 2 * prevRotation + !ccw;
	for (u32 test = 0; test < WK_TESTS; test++) {
		u32 i = test * 16 + u32(testOffset * 2);
		int offX = wkData[i];
		int offY = wkData[i + 1];
		if (!collides(offX, offY)) {
			pos.x += offX;
			pos.y += offY;
			return;
		}
	}
	// all tests failed, don't rotate piece
	shape = oldShape;
	rotation = prevRotation;
}

void Piece::update(const double dt, const u32 kDown, const u32 kHeld) {
	fallTimer += dt;
	if (kDown & KEY_DOWN ||
		fallTimer > ((kHeld & KEY_DOWN) ? sDropAfter : fallAfter)) {
		fallTimer = 0.0;
		move(Direction::DOWN);
	}

	if (collides(0, 1)) {
		setTimer += dt;
		if (hasSet()) {
			set();
			return;
		}
	} else {
		setTimer = 0.0;
	}

	if (kDown & KEY_UP) {
		while (move(Direction::DOWN)) {
		}
		setTimer = setAfter;
		set();
		return;
	}

	dasTimer.x = (kHeld & KEY_LEFT) ? dasTimer.x + dt : 0;
	dasTimer.y = (kHeld & KEY_RIGHT) ? dasTimer.y + dt : 0;

	updateMove(dt, kDown);

	if (kDown & KEY_Y) {
		rotate(true);
	}
	if (kDown & KEY_B) {
		rotate(false);
	}
}

void Piece::updateMove(const double dt, const u32 kDown) {
	auto _move = [this, &dt, &kDown](const Direction direction,
									 const double timer, const u32 kNeeded) {
		if (timer > das) {
			if (arr == 0.0) {
				while (move(direction)) {
				}
			} else {
				arrTimer -= dt;
				if (arrTimer <= 0.0) {
					move(direction);
					arrTimer = arr;
				}
			}

			return true;
		} else if (kDown & kNeeded) {
			move(direction);
			arrTimer = arr;

			return true;
		}

		return false;
	};

	bool moved =
		_move(LEFT, dasTimer.x, KEY_LEFT);  // x is actually the left timer
	if (!moved) {
		_move(RIGHT, dasTimer.y, KEY_RIGHT);  // y is actually the right timer
	}
}

PieceType Piece::getType() {
	return type;
}

bool Piece::hasSet() const {
	return setTimer >= setAfter;
}
