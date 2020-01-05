#pragma once

#include <3dstris/gui/widget.hpp>

class GUI;
class Slider : public Widget {
   public:
	Slider(GUI& parent, float x, float y, float w, float h, float ballSize);

	void draw() const override;
	void update(touchPosition touch, touchPosition) override;

	bool inside(float posX, float posY) const;

	float getValue() const;
	void setValue(float v);

   private:
	float x, y, w, h;
	float ballSize;
	float value;
	bool pressed;
};
