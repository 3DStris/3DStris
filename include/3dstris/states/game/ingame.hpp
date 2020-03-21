#pragma once

#include <3dstris/game/board.hpp>
#include <3dstris/state.hpp>
#include <deque>
#include <pcg_random.hpp>

class Ingame : public State {
   public:
	Ingame();

	virtual void reset();

	void update(double dt) override;
	void draw(bool bottom) const override;

   protected:
	Board board;
	u32 tileSize;
	Pos origin;

	pcg32_fast bagRNG;
	u32 upcoming;
	std::deque<PieceType> bag;

	Piece piece;

	PieceType hold;
	bool hasHeld;
};
