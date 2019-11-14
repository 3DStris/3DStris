#pragma once

#include <array>

namespace Shapes {
	PieceShape I = {
		0, 0, 0, 0,
		1, 1, 1, 1,
		0, 0, 0, 0,
		0, 0, 0, 0
	};

	PieceShape J = {
		1, 0, 0,
		1, 1, 1,
		0, 0, 0
	};

	PieceShape L = {
		0, 0, 1,
		1, 1, 1,
		0, 0, 0
	};

	PieceShape O = {
		1, 1,
		1, 1
	};
	
	PieceShape S = {
		0, 1, 1,
		1, 1, 0,
		0, 0, 0
	};

	PieceShape T = {
		0, 1, 0,
		1, 1, 1,
		0, 0, 0
	};

	PieceShape Z = {
		1, 1, 0,
		0, 1, 1,
		0, 0, 0
	};
};

std::array<PieceShape, 7> shapes{Shapes::I, Shapes::O, Shapes::L, Shapes::J, Shapes::S, Shapes::T, Shapes::Z};