#pragma once

#include <sds.h>

#include <3dstris/util/stringview.hpp>

struct String final {
	static String empty() noexcept;

	template <typename... Args>
	static String fromFmt(const char* __restrict fmt, Args&&... args) noexcept {
		return sdscatfmt(sdsempty(), fmt, args...);
	}

	template <typename... Args>
	static String fromPrintf(const char* __restrict fmt,
							 Args&&... args) noexcept {
		return sdscatprintf(sdsempty(), fmt, args...);
	}

	String() noexcept;
	String(sds str) noexcept;
	String(size_t len) noexcept;
	explicit String(StringView v) noexcept;
	String(const char* __restrict str) noexcept;
	String(const char* __restrict str, size_t len) noexcept;

	~String() noexcept;
	String(const String& str) noexcept;
	String(String&& str) noexcept;
	void operator=(const String& str) noexcept;
	void operator=(String&& str) noexcept;

	operator sds() const noexcept { return s; }
	operator StringView() const noexcept { return StringView(s, size()); }

	bool operator==(const String& str) const noexcept;
	bool operator!=(const String& str) const noexcept;
	bool operator<(const String& str) const noexcept;

	size_t size() const noexcept;
	size_t length() const noexcept;

	sds s;
};
