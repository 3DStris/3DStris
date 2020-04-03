#pragma once

#include <sds.h>
#include <string.h>

// Taken from sajson, I don't want to use any of its implementation details.
// Does not maintain any memory.
class StringLiteral final {
   public:
	template <size_t sz>
	constexpr StringLiteral(const char (&_text)[sz]) noexcept
		: text(_text), _length(sz - 1) {
		static_assert(sz > 0, "String must not be empty");
	}
	StringLiteral() = delete;

	constexpr const char* data() const noexcept { return text; }
	constexpr size_t length() const noexcept { return _length; }

   private:
	const char* text;
	const size_t _length;
};

struct String final {
	static String empty() noexcept { return sdsempty(); }

	template <typename... Args>
	static String fromFmt(const char* __restrict fmt, Args&&... args) noexcept {
		return sdscatfmt(sdsempty(), fmt, args...);
	}

	template <typename... Args>
	static String fromPrintf(const char* __restrict fmt,
							 Args&&... args) noexcept {
		return sdscatprintf(sdsempty(), fmt, args...);
	}

	String() noexcept : s(nullptr) {}
	String(const char* __restrict str) noexcept : s(sdsnew(str)) {}
	String(sds str) noexcept : s(str) {}
	String(const char* __restrict str, size_t len) noexcept
		: s(sdsnewlen(str, len)) {}
	String(size_t len) noexcept : s(sdsnewlen(nullptr, len)) {}
	String(const StringLiteral& str) : String(str.data(), str.length()) {}

	~String() noexcept { sdsfree(s); }
	String(const String& other) noexcept : s(sdsnew(other.s)) {}
	String(String&& other) noexcept : s(other.s) { other.s = nullptr; }
	void operator=(const String& other) noexcept {
		sdsfree(s);
		s = sdsnew(other.s);
	}
	void operator=(String&& other) noexcept {
		sdsfree(s);
		s = other.s;
		other.s = nullptr;
	}

	operator sds() const noexcept { return s; }

	bool operator==(const String& other) const noexcept {
		return sdscmp(s, other) == 0;
	}
	bool operator==(const char* __restrict str) const noexcept {
		const size_t len1 = length();
		const size_t len2 = strlen(str);
		return memcmp(s, str, (len1 < len2) ? len1 : len2);
	}

	template <size_t sz>
	bool operator==(const char (&str)[sz]) const noexcept {
		const size_t len1 = length();
		const size_t len2 = sz - 1;
		return memcmp(s, str, (len1 < len2) ? len1 : len2);
	}

	inline size_t length() const noexcept { return sdslen(s); }

	sds s;
};
