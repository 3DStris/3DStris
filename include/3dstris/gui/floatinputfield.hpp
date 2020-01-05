#pragma once

#include <3dstris/gui/widget.hpp>
#include <3dstris/util/text.hpp>

class GUI;
class FloatInputField : public Widget {
   public:
	FloatInputField(GUI& parent, float x, float y, float w, float h);

	void draw() const override;
	void update(touchPosition touch, touchPosition) override;

	bool inside(float posX, float posY) const;

	float getValue() const;
	void setValue(float v);

   private:
	void updateText();

	Text text;

	float x, y, w, h;
	float value;
	bool pressed;
};
