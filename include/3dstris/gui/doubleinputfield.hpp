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
	void updateText();

	Text text;
	sds suffix;

	float x, y, w, h;
	double value;

	bool held;
};
