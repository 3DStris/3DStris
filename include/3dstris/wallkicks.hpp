#pragma once

#include <array>

/*
 Wall kick data is stored as:
 Test n
   {spawn->ccw, spawn->cw, cw->spawn, cw->180, 180->cw, 180->ccw, ccw->180,
 ccw->spawn} More info on: https://harddrop.com/wiki/SRS
*/

constexpr unsigned int WK_TESTS = 5;

// 80 being 5 (number of tests) * 8 (number of conditions) * 2 (two numbers
// in each condition (x and y))
using Wallkick = std::array<int, 80>;

namespace Wallkicks {
	// clang-format off
	constexpr Wallkick I = {
		 0, 0,   0, 0,   0, 0,   0, 0,   0, 0,   0, 0,   0, 0,   0, 0,
		-1, 0,  -2, 0,   2, 0,  -1, 0,   1, 0,   2, 0,  -2, 0,   1, 0,
		 2, 0,   1, 0,  -1, 0,   2, 0,  -2, 0,  -1, 0,   1, 0,  -2, 0,
		-1,-2,  -2, 1,   2,-1,  -1,-2,   1, 2,   2,-1,  -2, 1,   1, 2,
		 2, 1,   1,-2,  -1, 2,   2, 1,  -2,-1,  -1, 2,   1,-2,  -2,-1
	};
	// couldn't think of a better name
	constexpr Wallkick OTHERS = {
		 0, 0,   0, 0,   0, 0,   0, 0,   0, 0,   0, 0,   0, 0,   0, 0,
		 1, 0,  -1, 0,   1, 0,   1, 0,  -1, 0,   1, 0,  -1, 0,  -1, 0,
		 1,-1,  -1,-1,   1, 1,   1, 1,  -1,-1,   1,-1,  -1, 1,  -1, 1,
		 0, 2,   0, 2,   0,-2,   0,-2,   0, 2,   0, 2,   0,-2,   0,-2,
		 1, 2,  -1, 2,   1,-2,   1,-2,  -1, 2,   1, 2,  -1,-2,  -1,-2
	};
	// clang-format on
}  // namespace Wallkicks
