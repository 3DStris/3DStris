#pragma once

#include <citro2d.h>

#include <array>
#include <memory>

// python-like modulo, which makes negative numbers wrap around
template <typename T>
constexpr T mod(T a, T b) {
	return (b + (a % b)) % b;
}

// We're on C++11; no std::make_unique
template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
constexpr auto SCREEN_WIDTH = 400;
constexpr auto SCREEN_HEIGHT = 240;

constexpr auto BSCREEN_WIDTH = 320;
constexpr auto BSCREEN_HEIGHT = 240;

using u32 = uint32_t;
using Color = u32;

struct Vector2 {
	float x;
	float y;
};

using Pos = Vector2;
using WH = Vector2;

struct Vector2d {
	double x;
	double y;
};

enum PieceType { I, O, L, J, S, T, Z, NONE };

enum Direction { LEFT, RIGHT, UP, DOWN };

static void straightLine(const Pos pos, const WH wh, const float thick,
						 const Color col, const float depth = 0.1f) {
	C2D_DrawRectSolid(pos.x - thick, pos.y - thick, depth, wh.x + thick,
					  wh.y + thick, col);
}
