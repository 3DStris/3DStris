#pragma once

#include <array>
#include <vector>

class PieceShape {
   public:
	using Shape = std::vector<bool>;

	PieceShape(const size_t size) : shape(size * size), _size(size) {}
	PieceShape(Shape&& shape, const size_t size) : shape(shape), _size(size) {}

	template <typename T>
	constexpr bool get(const T x, const T y) const noexcept {
		static_assert(std::is_arithmetic<T>::value, "T must be arithmetic");

		return inside(x, y) ? shape[index(x, y)] : false;
	}

	template <typename T>
	void set(const T x, const T y, const bool value = true) noexcept {
		static_assert(std::is_arithmetic<T>::value, "T must be arithmetic");

		if (inside(x, y)) {
			shape[index(x, y)] = value;
		}
	}

	template <typename T>
	constexpr bool inside(const T x, const T y) const noexcept {
		static_assert(std::is_arithmetic<T>::value, "T must be arithmetic");

		return index(x, y) < shape.size();
	}

	size_t size() const noexcept { return _size; }
	Shape& getShape() noexcept { return shape; }

   private:
	template <typename T>
	constexpr size_t index(const T x, const T y) const {
		static_assert(std::is_arithmetic<T>::value, "T must be arithmetic");

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

	const static std::array<const PieceShape, 7> ALL{
		Shapes::I, Shapes::O, Shapes::L, Shapes::J,
		Shapes::S, Shapes::T, Shapes::Z};
}  // namespace Shapes
