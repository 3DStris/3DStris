#pragma once

#include <3ds.h>
#include <citro2d.h>

class GUI;
class Slider {
   public:
	Slider(const GUI& parent, float x, float y, float w, float h, float ballSize);

	void draw() const;
	void update(touchPosition touch);

	bool inside(float posX, float posY) const;

	float getValue() const;
	void setValue(float v);

   private:
	const GUI& parent;

	float x, y, w, h;
	float ballSize;
	float value;
	bool pressed;
};
