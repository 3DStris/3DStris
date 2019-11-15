#pragma once

#include <3dstris/util.hpp>
#include <array>

namespace Shapes {
// clang-format off
	const PieceShape I = {
		0, 0, 0, 0,
		1, 1, 1, 1,
		0, 0, 0, 0,
		0, 0, 0, 0
	};

	const PieceShape J = { //
		1, 0, 0,
		1, 1, 1,
		0, 0, 0
	};

	const PieceShape L = {
		0, 0, 1,
		1, 1, 1,
		0, 0, 0
	};

	const PieceShape O = {
		1, 1,
		1, 1
	};
	
	const PieceShape S = {
		0, 1, 1,
		1, 1, 0,
		0, 0, 0
	};

	const PieceShape T = {
		0, 1, 0,
		1, 1, 1,
		0, 0, 0
	};

	const PieceShape Z = {
		1, 1, 0,
		0, 1, 1,
		0, 0, 0
	};
// clang-format on
};	// namespace Shapes

static std::array<PieceShape, 7> shapes{Shapes::I, Shapes::O, Shapes::L,
										Shapes::J, Shapes::S, Shapes::T,
										Shapes::Z};