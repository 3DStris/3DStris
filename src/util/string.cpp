#include <string.h>

#include <3dstris/util/string.hpp>

String String::empty() noexcept {
	return sdsempty();
}

String::String() noexcept : s(nullptr) {}
String::String(sds str) noexcept : s(str) {}
String::String(size_t len) noexcept : s(sdsnewlen(nullptr, len)) {}
String::String(const StringView v) noexcept : String(v.data(), v.length()) {}
String::String(const char* __restrict str) noexcept : s(sdsnew(str)) {}
String::String(const char* __restrict str, size_t len) noexcept
	: s(sdsnewlen(str, len)) {}

String::~String() noexcept {
	sdsfree(s);
}
String::String(const String& str) noexcept : s(sdsdup(str.s)) {}
String::String(String&& str) noexcept : s(str.s) {
	str.s = nullptr;
}

void String::operator=(const String& str) noexcept {
	sdsfree(s);
	s = sdsdup(str.s);
}
void String::operator=(String&& str) noexcept {
	sdsfree(s);
	s = str.s;
	str.s = nullptr;
}

bool String::operator==(const String& str) const noexcept {
	return sdscmp(s, str) == 0;
}
bool String::operator!=(const String& str) const noexcept {
	return !operator==(str);
}
bool String::operator<(const String& str) const noexcept {
	return sdscmp(s, str) < 0;
}

size_t String::size() const noexcept {
	return sdslen(s);
}
size_t String::length() const noexcept {
	return size();
}
