#include <3dstris/game.hpp>
#include <3dstris/game/board.hpp>
#include <3dstris/game/wallkicks.hpp>
#include <3dstris/util/colorstextures.hpp>

// Ching cong
Piece::Piece(Board& board, const PieceShape& shape, const PieceType type)
	: game(Game::get()), board(board), shape(shape) {
	reset(shape, type);
}

Piece::Piece(Board& board, const PieceType type)
	: Piece(board, Shapes::ALL[static_cast<size_t>(type)], type) {
	// Uhh
}

void Piece::reset(const PieceShape& shape, const PieceType type) {
	this->shape = shape;
	this->type = type;

	pos = {std::floor(board.width / 2.0f) - std::floor(shape.size() / 2.0f), 0};

	if (game.getConfig().useTextures) {
		sprite = Textures::get(static_cast<size_t>(type));
	}

	fallTimer = 0;
	fallAfter = 1;
	sDropAfter = game.getConfig().dropTimer / 1000.0;
	setTimer = 0;
	setAfter = 1;

	das = game.getConfig().das / 1000.0;
	dasTimer = {0, 0};

	arr = game.getConfig().arr / 1000.0;
	arrTimer = arr;

	rotation = 0;

	_dead =
		collides(0, 0);  // piece is "dead" if it collides as soon as it spawns
}

void Piece::reset(const PieceType type) {
	reset(Shapes::ALL[static_cast<size_t>(type)], type);
}

void Piece::set() {
	for (u8 y = 0; y < shape.size(); ++y) {
		for (u8 x = 0; x < shape.size(); ++x) {
			if (shape.get(x, y)) {
				board.set(pos.x + x, pos.y + y, type);
			}
		}
	}
	board.dropPiece();
	board.clearLines();
}

bool Piece::collides(const int offX, const int offY) const {
	for (u8 y = 0; y < shape.size(); ++y) {
		for (u8 x = 0; x < shape.size(); ++x) {
			const Vector2<int> offPos = {static_cast<int>(pos.x + x + offX),
										 static_cast<int>(pos.y + y + offY)};
			if (shape.get(x, y) && (!board.inside(offPos) ||
									board.get(offPos) != PieceType::NONE)) {
				return true;
			}
		}
	}
	return false;
}

void Piece::draw(const Pos origin, const u32 tileSize) const {
	int ghostY = 0;
	while (!collides(0, ++ghostY)) {
	}
	ghostY--;

	for (u8 y = 0; y < shape.size(); ++y) {
		for (u8 x = 0; x < shape.size(); ++x) {
			if (shape.get(x, y)) {
				const auto pieceX = origin.x + (pos.x + x) * tileSize;
				const auto pieceY = origin.y + (pos.y + y) * tileSize;
				const auto ghostPieceY =
					origin.y + (pos.y + ghostY + y) * tileSize;
				if (game.getConfig().useTextures) {
					C2D_DrawImageAt(sprite, pieceX, pieceY, 0.5f);
					C2D_DrawImageAt(sprite, pieceX, ghostPieceY, 0.5f,
									&Textures::GHOST);
				} else {
					C2D_DrawRectSolid(
						pieceX, pieceY, 0.5f, tileSize, tileSize,
						Textures::getColor(static_cast<size_t>(type)));
					C2D_DrawRectSolid(
						pieceX, ghostPieceY, 0.5f, tileSize, tileSize,
						Textures::getColor(static_cast<size_t>(type), true));
				}
			}
		}
	}
}

void Piece::draw(const Pos origin, const u32 tileSize, const PieceShape& shape,
				 const PieceType type) {
	for (u8 y = 0; y < shape.size(); ++y) {
		for (u8 x = 0; x < shape.size(); ++x) {
			if (shape.get(x, y)) {
				const auto pieceX = origin.x + x * tileSize;
				const auto pieceY = origin.y + y * tileSize;
				if (Game::get().getConfig().useTextures) {
					C2D_DrawImageAt(Textures::get(static_cast<size_t>(type)),
									pieceX, pieceY, 0.5f);
				} else {
					C2D_DrawRectSolid(
						pieceX, pieceY, 0.5f, tileSize, tileSize,
						Textures::getColor(static_cast<size_t>(type)));
				}
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
	if (type == PieceType::O) {
		return;
	}

	PieceShape newShape(shape.size());
	for (u32 y = 0; y < shape.size(); ++y) {
		for (u32 x = 0; x < shape.size(); ++x) {
			if (shape.get(x, y)) {
				if (ccw) {
					newShape.set(y, shape.size() - x - 1);
				} else {
					newShape
						.getShape()[x * shape.size() + shape.size() - y - 1] =
						true;
				}
			}
		}
	}
	const PieceShape oldShape = shape;
	shape = std::move(newShape);

	const int prevRotation = rotation;
	rotation = mod(rotation + (ccw ? -1 : 1), 4);

	const Wallkick wkData =
		type == PieceType::I ? Wallkicks::I : Wallkicks::OTHERS;

	/*
	 each test is stored as {spawn->ccw, spawn->cw, cw->spawn, cw->180,
	 180->cw, 180->ccw, ccw->180, ccw->spawn} considering spawn = 0, cw = 1, 180
	 = 2, ccw = 3 (aka add one when rotating clockwise, remove when counter
	 clockwise, and always mod 4) it becomes {0->3, 0->1, 1->0, 1->2, 2->1,
	 2->3, 3->2, 3->0} it's in that order so that:
	 [.., state->state after ccw, state->state after cw, ..]
	 which makes it easy to index by using: 2 * prevRotation + (ccw ? 0 : 1)
	 (ccw being true if the current rotation is counter clockwise)
	*/
	const int testOffset = 2 * prevRotation + !ccw;
	for (u8 test = 0; test < WK_TESTS; test++) {
		const u32 i = test * 16 + static_cast<u32>(testOffset * 2);
		const int offX = wkData[i];
		const int offY = wkData[i + 1];
		if (!collides(offX, offY)) {
			pos.x += offX;
			pos.y += offY;
			return;
		}
	}

	// all tests failed, don't rotate piece
	shape = std::move(oldShape);
	rotation = prevRotation;
}

void Piece::update(const double dt, const u32 kDown, const u32 kHeld) {
	fallTimer += dt;

	const bool softDropHeld = game.isPressed(kHeld, Keybinds::SOFT_DROP);
	if (sDropAfter == 0.0 && softDropHeld) {
		while (move(Direction::DOWN)) {
		}
		fallTimer = 0;
	} else if (softDropHeld ||
			   fallTimer > (softDropHeld ? sDropAfter : fallAfter)) {
		fallTimer = 0;
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

	if (game.isPressed(kDown, Keybinds::HARD_DROP)) {
		while (move(Direction::DOWN)) {
		}
		setTimer = setAfter;
		set();
		return;
	}

	dasTimer.x = game.isPressed(kHeld, Keybinds::LEFT) ? dasTimer.x + dt : 0;
	dasTimer.y = game.isPressed(kHeld, Keybinds::RIGHT) ? dasTimer.y + dt : 0;

	updateMove(dt, kDown);

	if (game.isPressed(kDown, Keybinds::ROTATE_CCW)) {
		rotate(true);
	} else if (game.isPressed(kDown, Keybinds::ROTATE_CW)) {
		rotate(false);
	}
}

void Piece::updateMove(const double dt, const u32 kDown) {
	const auto _move = [this, &dt, &kDown](
						   const Direction direction, const double timer,
						   const Keybinds::Action needed) -> bool {
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
		} else if (game.isPressed(kDown, needed)) {
			move(direction);
			arrTimer = arr;

			return true;
		}

		// didn't move;
		return false;
	};

	if (!_move(Direction::LEFT, dasTimer.x,  // x is actually the left timer
			   Keybinds::LEFT)) {
		_move(Direction::RIGHT, dasTimer.y,
			  Keybinds::RIGHT);  // y is actually the right timer
	}
}

PieceType Piece::getType() {
	return type;
}

bool Piece::hasSet() const {
	return setTimer >= setAfter;
}
