#pragma once

#include <3dstris/board.hpp>
#include <3dstris/shapes.hpp>
#include <3dstris/state.hpp>
#include <3dstris/states/mainmenu.hpp>
#include <3dstris/util.hpp>
#include <algorithm>
#include <array>
#include <cmath>
#include <deque>
#include <random>

class Playing : public State {
   public:
	Playing();

	void update(double dt) override;
	void draw(bool bottom) override;

   private:
	Color colBackground;

	Board board;
	const u32 tileSize;
	Vector2 origin;

	std::mt19937 bagRNG;
	const u32 upcoming;
	std::deque<PieceType> bag;

	Piece piece;

	PieceType hold;
	bool hasHeld;
};
