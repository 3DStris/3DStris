#pragma once

extern "C" {
#include <c2d/base.h>
}

#include <3dstris/util/math.hpp>

constexpr u32 SCREEN_WIDTH = 400;
constexpr u32 SCREEN_HEIGHT = 240;

constexpr u32 BSCREEN_WIDTH = 320;
constexpr u32 BSCREEN_HEIGHT = 240;

using Color = u32;
inline void straightLine(const Pos pos, const WH wh, const float thick,
						 const Color col, const float depth = 0.1f) noexcept {
	C2D_DrawRectSolid(pos.x - thick, pos.y - thick, depth, wh.x + thick,
					  wh.y + thick, col);
}
