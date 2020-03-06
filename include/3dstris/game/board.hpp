#pragma once

#include <3dstris/game/piece.hpp>

class Board {
   public:
	u32 width;
	u32 height;

	Board(const u32 width, const u32 height);

	void reset();

	template <typename T>
	constexpr bool inside(const T x, const T y) const noexcept {
		static_assert(std::is_arithmetic<T>::value, "T must be arithmetic");

		return x >= static_cast<T>(0) && y >= static_cast<T>(0) && x < width &&
			   y < height;
	}
	template <typename T>
	constexpr bool inside(const Vector2<T> pos) const noexcept {
		return inside(pos.x, pos.y);
	}

	template <typename T>
	void set(const T x, const T y, const PieceType t) {
		static_assert(std::is_arithmetic<T>::value, "T must be arithmetic");

		if (inside(x, y)) {
			grid[y * width + x] = t;
		}
	}
	template <typename T>
	void set(const Vector2<T> pos, const PieceType t) {
		set(pos.x, pos.y, t);
	}

	template <typename T>
	constexpr PieceType get(const T x, const T y) const {
		static_assert(std::is_arithmetic<T>::value, "T must be arithmetic");

		return inside(x, y) ? grid[y * width + x] : PieceType::INVALID;
	}
	template <typename T>
	constexpr PieceType get(const Vector2<T> pos) const {
		return get(pos.x, pos.y);
	}

	void draw(const Pos origin, const u32 tileSize,
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
