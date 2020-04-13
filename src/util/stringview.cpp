#include <string.h>

#include <3dstris/util/string.hpp>
#include <3dstris/util/stringview.hpp>

StringView::StringView(const String& str) noexcept
	: _data(str.s), _size(str.size()) {}

StringView::operator String() noexcept {
	return String(_data, _size);
}

bool operator==(const StringView lhs, const StringView rhs) noexcept {
	const size_t len1 = lhs.size();
	const size_t len2 = rhs.size();
	if (len1 != len2) {
		return false;
	}
	return memcmp(lhs.data(), rhs.data(), (len1 < len2) ? len1 : len2) == 0;
}

bool operator!=(const StringView lhs, const StringView rhs) noexcept {
	return !(lhs == rhs);
}
