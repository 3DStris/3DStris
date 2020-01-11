#pragma once

#include <3dstris/colors.hpp>
#include <3dstris/shapes.hpp>
#include <3dstris/util.hpp>
#include <3dstris/wallkicks.hpp>

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

	void update(const double dt, const u32 kDown, const u32 kHeld);

	PieceType getType();

	bool dead() const { return _dead; }

   private:
	void updateMove(const double dt, const u32 kDown);

	Board& board;

	PieceType type;
	Pos pos;

	int rotation;

	Color color;
	Color ghostColor;
	PieceShape shape;

	double
		fallTimer;  // timer that's between 0 and either fallAfter or dropTime
	double fallAfter;   // how much time it takes for the piece to fall
	double sDropAfter;  // replaces fallTimer when the soft drop button is held
	double setTimer;	// always 0 unless piece is colliding down, then it's
						// incremented until it gets to setAfter
	double setAfter;	// time it takes for piece to set after it has been
						// colliding down

	double das;
	// Vector2 as it needs one for left and right
	Vector2d dasTimer;

	double arr;
	double arrTimer;

	bool _dead;
};
