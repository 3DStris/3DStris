// Hashing taken from https://github.com/martinus/robin-hood-hashing,

// Copyright (c) 2018-2020 Martin Ankerl, 2020 Contributors to the 3DStris
// project

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

extern "C" {
#include <3ds/types.h>
}

#include <string.h>

#include <3dstris/util/hash.hpp>

template <typename T>
inline T unaligned_load(const void* ptr) noexcept {
	// using memcpy so we don't get into unaligned load problems.
	// compiler should optimize this very well anyways.
	T t;
	memcpy(&t, ptr, sizeof(T));
	return t;
}

#if __has_cpp_attribute(clang::fallthrough)
	#define FALLTHROUGH() [[clang::fallthrough]]
#elif __has_cpp_attribute(gnu::fallthrough)
	#define FALLTHROUGH() [[gnu::fallthrough]]
#else
	#define FALLTHROUGH()
#endif

static size_t hash_bytes(const void* ptr, const size_t len) noexcept {
	static constexpr u64 m = UINT64_C(0xc6a4a7935bd1e995);
	static constexpr u64 seed = UINT64_C(0xe17a1465);
	static constexpr u32 r = 47;

	const auto data64 = static_cast<const u64*>(ptr);
	u64 h = seed ^ (len * m);

	const size_t n_blocks = len / 8;
	for (size_t i = 0; i < n_blocks; ++i) {
		auto k = unaligned_load<u64>(data64 + i);

		k *= m;
		k ^= k >> r;
		k *= m;

		h ^= k;
		h *= m;
	}

	const auto data8 = reinterpret_cast<const u8*>(data64 + n_blocks);
	switch (len & 7U) {
		case 7:
			h ^= static_cast<u64>(data8[6]) << 48U;
			FALLTHROUGH();	// FALLTHROUGH
		case 6:
			h ^= static_cast<u64>(data8[5]) << 40U;
			FALLTHROUGH();	// FALLTHROUGH
		case 5:
			h ^= static_cast<u64>(data8[4]) << 32U;
			FALLTHROUGH();	// FALLTHROUGH
		case 4:
			h ^= static_cast<u64>(data8[3]) << 24U;
			FALLTHROUGH();	// FALLTHROUGH
		case 3:
			h ^= static_cast<u64>(data8[2]) << 16U;
			FALLTHROUGH();	// FALLTHROUGH
		case 2:
			h ^= static_cast<u64>(data8[1]) << 8U;
			FALLTHROUGH();	// FALLTHROUGH
		case 1:
			h ^= static_cast<u64>(data8[0]);
			h *= m;
			FALLTHROUGH();	// FALLTHROUGH
		default:
			break;
	}

	h ^= h >> r;
	h *= m;
	h ^= h >> r;
	return static_cast<size_t>(h);
}

size_t StringHash::operator()(StringView v) const {
	return hash_bytes(v.data(), v.length());
}
bool StringEq::operator()(StringView lhs, StringView rhs) const {
	return lhs == rhs;
}
