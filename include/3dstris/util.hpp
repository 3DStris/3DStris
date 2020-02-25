#pragma once

#include <citro2d.h>
#include <array>
#include <memory>

// python-like modulo, which makes negative numbers wrap around
template <typename T>
constexpr T mod(T a, T b) {
	static_assert(std::is_arithmetic<T>::value, "T must be arithmetic");

	return (b + (a % b)) % b;
}

// We're on C++11; no std::make_unique
template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
	static_assert(std::is_constructible<T, Args...>::value,
				  "Cannot construct T from passed Args");

	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

constexpr u16 SCREEN_WIDTH = 400;
constexpr u16 SCREEN_HEIGHT = 240;

constexpr u16 BSCREEN_WIDTH = 320;
constexpr u16 BSCREEN_HEIGHT = 240;

using u32 = uint32_t;
using Color = u32;

struct Vector2 {
	Vector2(const float x, const float y) : x(x), y(y) {}
	Vector2() {}

	float x = 0;
	float y = 0;
};

using Pos = Vector2;
using WH = Vector2;

struct Vector2d {
	Vector2d(const double x, const double y) : x(x), y(y) {}
	Vector2d() {}

	double x = 0;
	double y = 0;
};

enum PieceType { I, O, L, J, S, T, Z, NONE, INVALID };

enum Direction { LEFT, RIGHT, UP, DOWN };

static void straightLine(const Pos pos, const WH wh, const float thick,
						 const Color col, const float depth = 0.1f) {
	C2D_DrawRectSolid(pos.x - thick, pos.y - thick, depth, wh.x + thick,
					  wh.y + thick, col);
}
