#pragma once

#include <3dstris/gui/widget.hpp>
#include <3dstris/util/text.hpp>

class Button : public Widget {
   public:
	static constexpr Color BUTTON = C2D_Color32(33, 34, 48, 255);
	static constexpr Color BUTTON_OUTLINE = C2D_Color32(31, 32, 45, 255);
	static constexpr Color BUTTON_HELD = C2D_Color32(26, 27, 38, 255);

	enum Flags { NONE, HCENTER, VCENTER, CENTER };

	Button(GUI& parent, const Pos pos, const WH wh, const sds text,
		   const Flags flags = NONE);
	Button(GUI& parent, const Pos pos, const WH wh, const char* text,
		   const Flags flags = NONE);

	void setText(sds text);

	void draw() const override;
	void update(const touchPosition touch,
				const touchPosition previous) override;

	bool inside(const float x, const float y) const noexcept;
	bool pressed();

   private:
	Text text;

	bool held;
	bool _pressed;
};
