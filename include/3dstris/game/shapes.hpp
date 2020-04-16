#pragma once

extern "C" {
#include <3ds/types.h>
}

#include <array>
#include <vector>

class PieceShape {
   public:
	using Shape = std::vector<bool>;

	explicit PieceShape(size_t size) : shape(size * size), _size(size) {}
	PieceShape(Shape&& shape, size_t size) : shape(shape), _size(size) {}

	constexpr bool get(const u32 x, const u32 y) const noexcept {
		return inside(x, y) ? shape[index(x, y)] : false;
	}

	void set(const u32 x, const u32 y, const bool value = true) noexcept {
		if (inside(x, y)) {
			shape[index(x, y)] = value;
		}
	}

	constexpr bool inside(const u32 x, const u32 y) const noexcept {
		return index(x, y) < shape.size();
	}

	size_t size() const noexcept { return _size; }
	Shape& getShape() noexcept { return shape; }

   private:
	constexpr size_t index(const u32 x, const u32 y) const {
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

	static const std::array<std::reference_wrapper<const PieceShape>, 7> ALL{
		Shapes::I, Shapes::O, Shapes::L, Shapes::J,
		Shapes::S, Shapes::T, Shapes::Z};
}  // namespace Shapes
