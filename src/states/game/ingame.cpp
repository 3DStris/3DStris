#include <3dstris/states/game/ingame.hpp>
#include <3dstris/states/game/paused.hpp>

static std::array<PieceType, 7> genBag(pcg32_fast& rng) {
	std::array<PieceType, 7> pieces{PieceType::I, PieceType::O, PieceType::L,
									PieceType::J, PieceType::S, PieceType::T,
									PieceType::Z};

	pcg_extras::shuffle(pieces.begin(), pieces.end(), rng);
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

	const auto newBag = genBag(bagRNG);
	bag = std::deque<PieceType>(std::make_move_iterator(newBag.begin()),
								std::make_move_iterator(newBag.end()));

	piece.reset(bag.front());
	bag.pop_front();

	hold = PieceType::NONE;
	hasHeld = false;
}

void Ingame::update(const double dt) {
	const u32 kDown = hidKeysDown();
	const u32 kHeld = hidKeysHeld();
	if (kDown & KEY_START) {
		game.pushState(make_unique<Paused>(this));
		return;
	}

	assert(hold != PieceType::INVALID);
	assert(piece.getType() != PieceType::INVALID);

	piece.update(dt, kDown, kHeld);

	if (piece.hasSet()) {
		hasHeld = false;
		piece.reset(bag.front());
		bag.pop_front();
		if (bag.size() < upcoming) {
			auto tempBag = genBag(bagRNG);
			bag.insert(bag.end(), std::make_move_iterator(tempBag.begin()),
					   std::make_move_iterator(tempBag.end()));
		}
	}

	if (!hasHeld && game.isPressed(kDown, Keybinds::Action::HOLD)) {
		hasHeld = true;
		if (hold == PieceType::NONE && piece.getType() != PieceType::NONE) {
			hold = piece.getType();
			piece.reset(bag.front());
			bag.pop_front();
		} else {
			const auto tmp = piece.getType();
			piece.reset(hold);
			hold = tmp;
		}
	}
}

void Ingame::draw(const bool bottom) {
	if (bottom) {
		return;
	}
	C2D_TargetClear(game.getTop(), game.getTheme().background);

	board.draw(origin, tileSize);
	piece.draw(origin, tileSize);

	// draw bag
	u32 y = 1;
	for (u32 i = 0; i < upcoming; ++i) {
		const PieceType& p = bag[i];

		if (p == PieceType::I) {
			--y;
		}

		Piece::draw(
			{origin.x + (board.width + 1 + (p == PieceType::O)) * tileSize,
			 origin.y + y * tileSize},
			tileSize, Shapes::ALL[static_cast<size_t>(p)], p);

		y += Shapes::ALL[static_cast<size_t>(p)].get().size();
		if (p == PieceType::O) {
			++y;
		}
	}

	// draw held piece
	if (hold != PieceType::NONE && hold != PieceType::INVALID) {
		Piece::draw(
			{origin.x -
				 (Shapes::ALL[static_cast<size_t>(hold)].get().size() + 1) *
					 tileSize,
			 origin.y + tileSize},
			tileSize, Shapes::ALL[static_cast<size_t>(hold)], hold);
	}
}
