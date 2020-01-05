#pragma once

#include <3ds.h>
#include <citro2d.h>
#include <3dstris/gui/widget.hpp>
#include <3dstris/util/text.hpp>
#include <functional>

class GUI;
class Button : public Widget {
   public:
	Button(GUI& parent, float x, float y, float w, float h, sds text);
	Button(GUI& parent, float x, float y, float w, float h, const char* text);

	void setText(sds text);

	void draw() const override;
	void update(touchPosition touch, touchPosition previous) override;

	bool inside(float posX, float posY) const;
	bool pressed();

   private:
	Text text;

	float x, y, w, h;
	bool held;
	bool _pressed;
};
