#pragma once

#include <3dstris/gui/widget.hpp>
#include <3dstris/util/text.hpp>

class Button : public Widget {
   public:
	enum class Flags { NONE, HCENTER, VCENTER, CENTER };

	Button(GUI& parent, Pos pos, WH wh, sds text, Flags flags = Flags::NONE);
	Button(GUI& parent, Pos pos, WH wh, const char* __restrict text,
		   Flags flags = Flags::NONE);

	void setText(sds text);

	void draw() const override;
	void update(touchPosition touch, touchPosition previous) override;

	bool inside(float x, float y) const noexcept;
	bool pressed();

   private:
	Text text;

	bool held = false;
	bool _pressed = false;
};
