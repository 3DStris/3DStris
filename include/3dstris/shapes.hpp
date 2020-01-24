#pragma once

#include <3dstris/util.hpp>
#include <array>
#include <vector>

class PieceShape {
   public:
	using Shape = std::vector<bool>;

	PieceShape(const size_t size) : shape(size * size), _size(size) {}
	PieceShape(Shape&& shape, const size_t size) : shape(shape), _size(size) {}

	template <typename T>
	bool get(const T x, const T y) const noexcept {
		return inside(x, y) ? shape[index(x, y)] : false;
	}

	template <typename T>
	void set(const T x, const T y, const bool value = true) noexcept {
		if (inside(x, y)) {
			shape[index(x, y)] = value;
		}
	}

	template <typename T>
	bool inside(const T x, const T y) const noexcept {
		return index(x, y) < shape.size();
	}

	size_t size() const noexcept { return _size; }
	Shape& getShape() noexcept { return shape; }

   private:
	template <typename T>
	constexpr size_t index(const T x, const T y) const {
		return y * _size + x;
	}

	Shape shape;
	size_t _size;
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
};  // namespace Shapes

static std::array<PieceShape, 7> shapes{Shapes::I, Shapes::O, Shapes::L,
										Shapes::J, Shapes::S, Shapes::T,
										Shapes::Z};
