#pragma once

#include <3dstris/piece.hpp>
#include <vector>

class Board {
   public:
	u32 width;
	u32 height;

	Board(const u32 width, const u32 height);

	void reset();

	template <typename T>
	bool inside(T x, T y) {
		return x < width && y < height;
	}
	bool inside(const Pos pos);

	template <typename T>
	void set(const T x, const T y, const PieceType t) {
		if (inside(x, y)) {
			grid[y * width + x] = t;
		}
	}
	void set(const Pos pos, const PieceType t);

	template <typename T>
	PieceType get(const T x, const T y) const {
		return grid[y * width + x];
	}
	PieceType get(const Pos pos) const;

	void draw(const Vector2 origin, const u32 tileSize,
			  const float outerThick = 1.75, const float gridThick = 1) const;

	void clearLines();

	void dropPiece() noexcept { _droppedPieces++; }
	u32 droppedPieces() const noexcept { return _droppedPieces; }

	u32 linesCleared() const noexcept { return _linesCleared; }

   private:
	std::vector<PieceType> grid;

	u32 _droppedPieces;
	u32 _linesCleared;
};
