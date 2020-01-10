#pragma once

#include <3ds.h>
#include <3dstris/util.hpp>

class GUI;
class Widget {
   public:
	Widget(GUI& parent, Vector2 pos, Vector2 wh);
	virtual ~Widget() = default;

	Widget(const Widget&) = delete;
	Widget(Widget&&) = delete;
	Widget& operator=(const Widget&) = delete;
	Widget& operator=(Widget&&) = delete;

	virtual void draw() const = 0;
	virtual void update(touchPosition touch, touchPosition previousTouch) = 0;

	Vector2 getPos() const noexcept { return pos; }
	Vector2 getWH() const noexcept { return wh; }

   protected:
	GUI& parent;

	Vector2 pos;
	Vector2 wh;
};
