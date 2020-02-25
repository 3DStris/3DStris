#pragma once

#include <3dstris/game/board.hpp>
#include <3dstris/state.hpp>
#include <deque>
#include <random>

class Ingame : public State {
   public:
	Ingame();

	virtual void reset();

	void update(const double dt) override;
	void draw(const bool bottom) override;

   protected:
	Board board;
	const u8 tileSize;
	Vector2 origin;

	std::mt19937_64 bagRNG;
	const u8 upcoming;
	std::deque<PieceType> bag;

	Piece piece;

	PieceType hold;
	bool hasHeld;
};
