#pragma once

#include <3dstris/gui/widget.hpp>
#include <3dstris/util/text.hpp>

class Button : public Widget {
   public:
	enum class Flags { NONE, HCENTER, VCENTER, CENTER };

	Button(GUI& parent, Pos pos, WH wh, String&& text = String::empty(),
		   Flags flags = Flags::NONE) noexcept;

	void setText(String&& text) noexcept;

	void draw() const noexcept override;
	void update(touchPosition touch, touchPosition previous) override;

	bool inside(float x, float y) const noexcept;
	bool pressed() noexcept;

   private:
	inline void scaleAlignText() noexcept {
		this->text.scale(wh.x, 0.7f);
		this->text.align(Text::Align::CENTER, Pos{pos.x, pos.y},
						 WH{wh.x, wh.y});
	}

	Text text;

	bool held = false;
	bool _pressed = false;
};
