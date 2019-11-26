#pragma once

#include <citro2d.h>
#include <3dstris/board.hpp>
#include <3dstris/shapes.hpp>
#include <3dstris/state.hpp>
#include <3dstris/util.hpp>
#include <3dstris/states/mainmenu.hpp>
#include <algorithm>
#include <array>
#include <cmath>
#include <deque>
#include <random>

std::array<PieceType, 7> genBag(std::mt19937& rng);

class Playing : public State {
public:
	Playing(Game& game);

	void update(double dt);
	void draw(bool bottom);
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