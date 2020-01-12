#pragma once

#include <3dstris/piece.hpp>
#include <vector>

class Board {
   public:
	u32 width;
	u32 height;

	Board(u32 width, u32 height);

	void reset();

	template <typename T>
	bool inside(T x, T y) {
		return x < width && y < height;
	}
	bool inside(Pos pos);

	template <typename T>
	void set(T x, T y, PieceType t) {
		if (inside(x, y)) {
			grid[y * width + x] = t;
		}
	}
	void set(Pos pos, PieceType t);

	template <typename T>
	PieceType get(T x, T y) const {
		return grid[y * width + x];
	}
	PieceType get(Pos pos) const;

	void draw(Vector2 origin, u32 tileSize, int outerThick = 2,
			  int gridThick = 1) const;

	void clearLines();

	void dropPiece() noexcept { _droppedPieces++; }
	u32 droppedPieces() const noexcept { return _droppedPieces; }

	u32 linesCleared() const noexcept { return _linesCleared; }

   private:
	std::vector<PieceType> grid;

	u32 _droppedPieces;
	u32 _linesCleared;
};
