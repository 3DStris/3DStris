#pragma once

#include <3dstris/gui/widget.hpp>
#include <3dstris/util/text.hpp>

class GUI;
class Button : public Widget {
   public:
	enum Flags { NONE, HCENTER, VCENTER, CENTER };

	static constexpr Color BUTTON = C2D_Color32(79, 79, 79, 255);
	static constexpr Color BUTTON_OUTLINE = C2D_Color32(89, 89, 89, 255);
	static constexpr Color BUTTON_HELD = C2D_Color32(64, 64, 64, 255);

	Button(GUI& parent, const Pos pos, const WH wh, const sds text,
		   const Flags flags = NONE);
	Button(GUI& parent, const Pos pos, const WH wh, const char* text,
		   const Flags flags = NONE);

	void setText(sds text);

	void draw() const override;
	void update(const touchPosition touch,
				const touchPosition previous) override;

	bool inside(const float posX, const float posY) const;
	bool pressed();

   private:
	Text text;

	bool held;
	bool _pressed;
};
