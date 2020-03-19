#pragma once

#include <memory>

// We're on C++11; no std::make_unique
template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
	static_assert(std::is_constructible<T, Args...>::value,
				  "Cannot construct T from passed Args");

	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
