#pragma once

#include <3dstris/piece.hpp>
#include <vector>

class Board {
   public:
	u32 width;
	u32 height;

	Board(u32 width, u32 height);

    bool inside(u32 x, u32 y);
	bool inside(int x, int y);
	bool inside(Vector2 pos);

	void set(u32 x, u32 y, PieceType t);
	void set(int x, int y, PieceType t);
	void set(Vector2 pos, PieceType t);

	PieceType get(u32 x, u32 y) const;
	PieceType get(Vector2 pos) const;

	void draw(Vector2 origin, u32 tileSize, int outerThick = 2,
			  int gridThick = 1) const;

	void clearLines();

   private:
	std::vector<PieceType> grid;
};
