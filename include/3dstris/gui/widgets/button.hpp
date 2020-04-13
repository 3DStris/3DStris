#pragma once

#include <3dstris/gui.hpp>
#include <3dstris/gui/widget.hpp>
#include <3dstris/util/text.hpp>

class Button : public Widget {
   public:
	enum class Flags { NONE, HCENTER, VCENTER, CENTER };

	template <typename T>
	Button(GUI& _parent, Pos _pos, WH _wh, T&& text = String::empty(),
		   Flags flags = Flags::NONE) noexcept
		: Widget(_parent, _pos, _wh), text(text) {
		if (flags == Flags::HCENTER || flags == Flags::CENTER) {
			pos.x = (parent.getWidth() - wh.x) / 2.0f;
		}
		if (flags == Flags::VCENTER || flags == Flags::CENTER) {
			pos.y = (parent.getHeight() - wh.y) / 2.0f;
		}

		scaleAlignText();
	}

	template <typename T>
	void setText(T&& text) noexcept {
		this->text.setText(text);
		scaleAlignText();
	}

	void draw() const noexcept override;
	void update(touchPosition touch, touchPosition previous) override;

	bool inside(float x, float y) const noexcept;
	bool pressed() noexcept;

   protected:
	Text text;

   private:
	inline void scaleAlignText() noexcept {
		text.scale(wh.x, 0.7f);
		text.align(Text::Align::CENTER, Pos{pos.x, pos.y}, WH{wh.x, wh.y});
	}

	bool held = false;
	bool _pressed = false;
};
