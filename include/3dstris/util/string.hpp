#pragma once

#include <sds.h>

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

	sds s;
};
