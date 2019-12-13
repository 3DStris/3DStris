#pragma once

#include <3ds.h>
#include <citro2d.h>
#include <3dstris/util/text.hpp>
#include <functional>

class GUI;
class Button {
   public:
	Button(const GUI& parent, float x, float y, float w, float h,
		   const char* text, std::function<void()> onPress);

	void setText(const char* text);

	void draw() const;
	void update(touchPosition touch);

	bool inside(float posX, float posY) const;
	void press();

   private:
	const GUI& parent;

	Text text;

	float x, y, w, h;
	bool pressed;
	std::function<void()> onPress;
};
