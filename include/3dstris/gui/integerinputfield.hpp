#pragma once

#include <3dstris/gui/widget.hpp>
#include <3dstris/util/text.hpp>

class GUI;

template <typename T = u32, u8 digits = 6>
class IntegerInputField : public Widget {
	static_assert(std::is_integral<T>::value, "T must be integral");
	static_assert(digits <= 21, "Cannot use more than 21 digits");

   public:
	IntegerInputField(GUI& _parent, const Pos _pos, const WH _wh,
					  const sds suffix = sdsempty())
		: Widget(_parent, _pos, _wh), suffix(suffix), value(0) {
		updateText();
	}
	IntegerInputField(GUI& _parent, const Pos _pos, const WH _wh,
					  const char* __restrict suffix)
		: IntegerInputField(_parent, _pos, _wh, sdsnew(suffix)) {}

	~IntegerInputField() override { sdsfree(suffix); }

	void draw() const override {
		C2D_DrawRectSolid(pos.x, pos.y, 0, wh.x, wh.y,
						  held ? FIELD_HELD : FIELD);
		text.draw();
	}

	void update(const touchPosition touch,
				const touchPosition previous) override {
		held = inside(touch.px, touch.py);

		if (inside(previous.px, previous.py) && hidKeysUp() & KEY_TOUCH) {
			SwkbdState swkbd;
			swkbdInit(&swkbd, SWKBD_TYPE_NUMPAD, 1, digits);
			swkbdSetValidation(&swkbd, SWKBD_NOTEMPTY_NOTBLANK, 0, 0);
			swkbdSetFeatures(&swkbd, SWKBD_FIXED_WIDTH);

			sds initialText = sdsfromlonglong(value);
			swkbdSetInitialText(&swkbd, initialText);
			sdsfree(initialText);

			sds buf = sdsnewlen("", digits + 1);
			swkbdInputText(&swkbd, buf, digits + 1);

			char* end;
			errno = 0;
			const T tempValue = std::is_signed<T>::value
									? strtoll(buf, &end, 10)
									: strtoull(buf, &end, 10);
			if (end[0] == '\0' && errno == 0) {
				value = tempValue;
				updateText();
			}
			sdsfree(buf);
		}
	}

	bool inside(const float x, const float y) const {
		return x > pos.x && x < pos.x + wh.x &&  //
			   y > pos.y && y < pos.y + wh.y;
	}

	T getValue() const noexcept { return value; }
	void setValue(const T value) {
		this->value = value;
		updateText();
	}

   private:
	static constexpr Color FIELD = C2D_Color32(30, 32, 47, 255);
	static constexpr Color FIELD_HELD = C2D_Color32(28, 30, 44, 255);

	void updateText() {
		text.setText(sdscatfmt(
			sdsempty(), std::is_signed<T>::value ? "%I%S" : "%U%S",
			std::is_signed<T>::value ? s64(value) : u64(value), suffix));

		const float textScale = std::min(text.getWH().y / wh.y, 0.5f);
		text.setScale({textScale, textScale});

		text.align(Text::Align::VCENTER, pos, wh);
		text.setX(pos.x + 3);
	}

	Text text;
	sds suffix;

	T value;

	bool held;
};
