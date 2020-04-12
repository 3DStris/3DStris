#include <string.h>

#include <3dstris/util/hash.hpp>

// Hashing taken from https://github.com/martinus/robin-hood-hashing
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
	static constexpr uint64_t m = UINT64_C(0xc6a4a7935bd1e995);
	static constexpr uint64_t seed = UINT64_C(0xe17a1465);
	static constexpr unsigned int r = 47;

	const auto data64 = static_cast<const uint64_t*>(ptr);
	uint64_t h = seed ^ (len * m);

	const size_t n_blocks = len / 8;
	for (size_t i = 0; i < n_blocks; ++i) {
		auto k = unaligned_load<uint64_t>(data64 + i);

		k *= m;
		k ^= k >> r;
		k *= m;

		h ^= k;
		h *= m;
	}

	const auto data8 = reinterpret_cast<const uint8_t*>(data64 + n_blocks);
	switch (len & 7U) {
		case 7:
			h ^= static_cast<uint64_t>(data8[6]) << 48U;
			FALLTHROUGH();	// FALLTHROUGH
		case 6:
			h ^= static_cast<uint64_t>(data8[5]) << 40U;
			FALLTHROUGH();	// FALLTHROUGH
		case 5:
			h ^= static_cast<uint64_t>(data8[4]) << 32U;
			FALLTHROUGH();	// FALLTHROUGH
		case 4:
			h ^= static_cast<uint64_t>(data8[3]) << 24U;
			FALLTHROUGH();	// FALLTHROUGH
		case 3:
			h ^= static_cast<uint64_t>(data8[2]) << 16U;
			FALLTHROUGH();	// FALLTHROUGH
		case 2:
			h ^= static_cast<uint64_t>(data8[1]) << 8U;
			FALLTHROUGH();	// FALLTHROUGH
		case 1:
			h ^= static_cast<uint64_t>(data8[0]);
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
