#pragma once

#include <3dstris/game.hpp>
#include <3dstris/game/shapes.hpp>
#include <3dstris/util.hpp>

class Board;
class Piece {
   public:
	Piece(Board& board, const PieceShape& shape, const PieceType type);
	Piece(Board& board, const PieceType type);

	void reset(const PieceShape& shape, const PieceType type);
	void reset(const PieceType type);

	void set();

	void draw(const Pos origin, const u32 tileSize) const;
	static void draw(const Pos origin, const u32 tileSize,
					 const PieceShape& shape, const PieceType type);

	bool move(const Direction dir);

	void rotate(const bool ccw);

	bool collides(const int offX, const int offY) const;
	bool hasSet() const;

	void update(const double dt, const u32 kDown, const u32 kHeld);

	PieceType getType();

	bool dead() const { return _dead; }

   private:
	const Game& game;

	void updateMove(const double dt, const u32 kDown);

	Board& board;

	PieceType type;
	Pos pos;

	int rotation;

	C2D_Image sprite;
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
	Vector2d dasTimer;  // Vector2 as it needs one for left and right

	double arr;
	double arrTimer;

	bool _dead;
};
