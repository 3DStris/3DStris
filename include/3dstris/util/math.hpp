#pragma once

extern "C" {
#include <3ds/types.h>
}

#include <type_traits>

// python-like modulo, which makes negative numbers wrap around
template <typename T>
constexpr T mod(const T a, const s32 b) noexcept {
	static_assert(std::is_arithmetic<T>::value, "T must be arithmetic");

	return (b + (a % b)) % b;
}

template <typename T>
struct Vector2 {
	static_assert(std::is_arithmetic<T>::value, "T must be arithmetic");

	constexpr Vector2() noexcept {}
	constexpr Vector2(const T x, const T y) noexcept : x(x), y(y) {}

	T x = 0;
	T y = 0;
};

using Vector2f = Vector2<float>;
using Vector2d = Vector2<double>;

using Pos = Vector2f;
using WH = Vector2f;
