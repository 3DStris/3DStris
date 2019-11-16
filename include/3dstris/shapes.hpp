#pragma once

#include <3dstris/util.hpp>
#include <array>
#include <vector>

struct PieceShape {
	std::vector<bool> shape;
	u32 size;
};

namespace Shapes {
// clang-format off
	const PieceShape I = {{
		0, 0, 0, 0,
		1, 1, 1, 1,
		0, 0, 0, 0,
		0, 0, 0, 0
	}, 4};

	const PieceShape J = {{
		1, 0, 0,
		1, 1, 1,
		0, 0, 0
	}, 3};

	const PieceShape L = {{
		0, 0, 1,
		1, 1, 1,
		0, 0, 0
	}, 3};

	const PieceShape O = {{
		1, 1,
		1, 1
	}, 2};
	
	const PieceShape S = {{
		0, 1, 1,
		1, 1, 0,
		0, 0, 0
	}, 3};

	const PieceShape T = {{
		0, 1, 0,
		1, 1, 1,
		0, 0, 0
	}, 3};

	const PieceShape Z = {{
		1, 1, 0,
		0, 1, 1,
		0, 0, 0
	}, 3};
// clang-format on
};	// namespace Shapes

static std::array<PieceShape, 7> shapes{Shapes::I, Shapes::O, Shapes::L,
										Shapes::J, Shapes::S, Shapes::T,
										Shapes::Z};