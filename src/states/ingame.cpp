#include <3dstris/states/ingame.hpp>
#include <algorithm>

static std::array<PieceType, 7> genBag(std::mt19937_64& rng) {
	std::array<PieceType, 7> pieces{PieceType::I, PieceType::O, PieceType::L,
									PieceType::J, PieceType::S, PieceType::T,
									PieceType::Z};
	std::shuffle(pieces.begin(), pieces.end(), rng);
	return pieces;
}

Ingame::Ingame()
	: State(),
	  board(10, 20),
	  tileSize((SCREEN_HEIGHT - 10) / board.height),
	  bagRNG(osGetTime()),
	  upcoming(5),
	  piece(board, PieceType::I) {
	origin = {(SCREEN_WIDTH - board.width * tileSize) / 2.0f, 10};
	reset();
}

void Ingame::reset() {
	board.reset();

	const auto _bag = genBag(bagRNG);
	bag = std::deque<PieceType>(_bag.begin(), _bag.end());

	piece.reset(bag.front());
	bag.pop_front();

	hold = PieceType::NONE;
	hasHeld = false;
}

void Ingame::update(const double dt) {
	u32 kDown = hidKeysDown();
	u32 kHeld = hidKeysHeld();

	piece.update(dt, kDown, kHeld);

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
		if (hold == PieceType::NONE) {
			hold = piece.getType();
			piece.reset(bag.front());
			bag.pop_front();
		} else {
			PieceType tmp = piece.getType();
			piece.reset(hold);
			hold = tmp;
		}
	}
}

void Ingame::draw(const bool bottom) {
	if (!bottom) {
		C2D_TargetClear(this->game.getTop(), BACKGROUND);

		board.draw(origin, tileSize);
		piece.draw(origin, tileSize);

		// draw bag
		u32 y = 1;
		for (u32 i = 0; i < upcoming; ++i) {
			const auto& p = bag[i];

			if (p == PieceType::I) {
				--y;
			}

			Piece::draw(
				{origin.x + (board.width + 1 + (p == PieceType::O)) * tileSize,
				 origin.y + y * tileSize},
				tileSize, shapes[p], colors[p]);

			y += shapes[p].size();
			if (p == PieceType::O) {
				++y;
			}
		}

		// draw held piece
		if (hold != PieceType::NONE) {
			Piece::draw({origin.x - (shapes[hold].size() + 1) * tileSize,
						 origin.y + tileSize},
						tileSize, shapes[hold], colors[hold]);
		}
	}
}
