#pragma once

#include <3dstris/util.hpp>

class Board;
class Piece {
   private:
	float fallTimer;
	PieceShape shape;
	int size;
	// Vector2 as they need one for left and right
	Vector2 dasTimer;
	float arr;
	float arrTimer;
	Board& board;
	float das;
	Color color;
	Color ghostColor;

   public:
	Vector2 pos;
	PieceType type;
	bool hasSet;

	Piece(Board& board, PieceShape shape, PieceType type);

	void reset(PieceShape shape, PieceType type);

	void set();

	bool collides(int offX, int offY);

	void draw(Vector2 origin, int tileSize);

	static void draw(Vector2 origin, int tileSize, PieceShape& shape,
					 Color color);

	bool move(Direction dir);

	void rotate(bool ccw);

	void update(float dt, u32 kDown, u32 kHeld);
};