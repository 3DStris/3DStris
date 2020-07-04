#pragma once

#include <stddef.h>

struct String;
class StringView final {
   public:
	constexpr StringView() noexcept : _data(nullptr), _size(0) {}

	template <size_t sz>
	constexpr StringView(const char (&_text)[sz]) noexcept
		: _data(_text), _size(sz - 1) {
		static_assert(sz > 0, "String must not be empty");
	}
	constexpr StringView(const char* __restrict _text, size_t len) noexcept
		: _data(_text), _size(len) {}
	explicit StringView(const String& str) noexcept;

	constexpr StringView(const StringView& v) noexcept = default;
	StringView& operator=(const StringView& v) noexcept = default;

	explicit operator String() const noexcept;

	constexpr const char* data() const noexcept { return _data; }
	constexpr size_t size() const noexcept { return _size; }
	constexpr size_t length() const noexcept { return size(); }

   private:
	const char* _data;
	size_t _size;
};

bool operator==(StringView lhs, StringView rhs) noexcept;
bool operator!=(StringView lhs, StringView rhs) noexcept;
