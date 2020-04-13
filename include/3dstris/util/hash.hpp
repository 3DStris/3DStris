#pragma once

#include <3dstris/util/string.hpp>

struct StringHash {
	using is_transparent = void;

	size_t operator()(StringView v) const;
};

struct StringEq {
	using is_transparent = void;

	bool operator()(StringView lhs, StringView rhs) const;
};
