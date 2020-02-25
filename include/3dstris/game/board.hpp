#pragma once

#include <3dstris/game/piece.hpp>

class Board {
   public:
	u16 width;
	u16 height;

	Board(const u16 width, const u16 height);

	void reset();

	template <typename T>
	bool inside(const T x, const T y) const noexcept {
		static_assert(std::is_arithmetic<T>::value, "T must be arithmetic");

		return x < width && y < height;
	}
	bool inside(const Pos pos) const noexcept;

	template <typename T>
	void set(const T x, const T y, const PieceType t) {
		static_assert(std::is_arithmetic<T>::value, "T must be arithmetic");

		if (inside(x, y)) {
			grid[y * width + x] = t;
		}
	}
	void set(const Pos pos, const PieceType t);

	template <typename T>
	PieceType get(const T x, const T y) const {
		static_assert(std::is_arithmetic<T>::value, "T must be arithmetic");

		if (inside(x, y)) {
			return grid[y * width + x];
		}
		return PieceType::INVALID;
	}
	PieceType get(const Pos pos) const;

	void draw(const Vector2 origin, const u8 tileSize,
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
