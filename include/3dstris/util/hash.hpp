#pragma once

#include <robin_hood.h>

#include <3dstris/util/string.hpp>

template <typename T>
struct Hash : public robin_hood::hash<T> {};

template <>
struct Hash<String> {
	size_t operator()(const String& str) const noexcept {
		return robin_hood::hash_bytes(str.s - 1, str.length());
	}
};
