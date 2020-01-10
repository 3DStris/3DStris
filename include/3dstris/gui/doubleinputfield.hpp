#pragma once

#include <3dstris/gui/widget.hpp>
#include <3dstris/util/text.hpp>

class GUI;
class DoubleInputField : public Widget {
   public:
	DoubleInputField(GUI& parent, float x, float y, float w, float h,
					 const sds suffix = sdsempty());
	DoubleInputField(GUI& parent, float x, float y, float w, float h,
					 const char* suffix);
	~DoubleInputField() override;

	void draw() const override;
	void update(touchPosition touch, touchPosition) override;

	bool inside(float posX, float posY) const;

	double getValue() const;
	void setValue(double v);

   private:
	static constexpr Color FIELD = C2D_Color32(94, 94, 94, 255);
	static constexpr Color FIELD_HELD = C2D_Color32(75, 75, 75, 255);

	void updateText();

	Text text;
	sds suffix;

	double value;

	bool held;
};
