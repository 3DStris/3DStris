#pragma once

#include <citro2d.h>

#include <array>
#include <vector>

// python-like modulo, which makes negative numbers wrap around
template <typename T>
constexpr T mod(T a, T b) {
	return (b + (a % b)) % b;
}

// from https://github.com/henrygab/UtilHeaders/blob/master/constexpr_strlen.h
template <size_t N>
constexpr size_t constexpr_strlen(char const (&)[N]) {
	return N - 1;
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

struct Vector2d {
	double x;
	double y;
};

enum PieceType { I, O, L, J, S, T, Z, None };

enum Direction { left, right, up, down };

static void straightLine(float x, float y, float w, float h, float thick,
						 Color col) {
	C2D_DrawRectSolid(x - thick, y - thick, 0.0f, w + thick, h + thick, col);
}
