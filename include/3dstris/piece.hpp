#pragma once

#include <3dstris/util.hpp>
#include <3dstris/shapes.hpp>

class Board;
class Piece {
   public:
	Piece(Board& board, const PieceShape& shape, const PieceType type);
	Piece(Board& board, const PieceType type);

	void reset(const PieceShape& shape, const PieceType type);
	void reset(const PieceType type);

	void set();

	void draw(const Vector2 origin, const u32 tileSize) const;
	static void draw(const Vector2 origin, const u32 tileSize,
					 const PieceShape& shape, const Color color);

	bool move(const Direction dir);

	void rotate(const bool ccw);

	bool collides(const int offX, const int offY) const;
	bool hasSet() const;

	void update(const float dt, const u32 kDown, const u32 kHeld);

	PieceType getType();

   private:
	Board& board;

	PieceType type;
	Vector2 pos;

	Color color;
	Color ghostColor;
	PieceShape shape;

	float fallTimer; // timer that's between 0 and either fallAfter or dropTime
	float fallAfter; // how much time it takes for the piece to fall
	float sDropAfter; // replaces fallTimer when the soft drop button is held
	float setTimer; // always 0 unless piece is colliding down, then it's incremented until it gets to setAfter
	float setAfter; // time it takes for piece to set after it has been colliding down

	float das;
	// Vector2 as it needs one for left and right
	Vector2 dasTimer;

	float arr;
	float arrTimer;
};