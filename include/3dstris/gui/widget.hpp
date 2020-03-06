#pragma once

#include <3dstris/util.hpp>

class GUI;
class Widget {
   public:
	Widget(GUI& parent, Pos pos, WH wh);
	virtual ~Widget() = default;

	virtual void draw() const = 0;
	virtual void update(touchPosition touch, touchPosition previousTouch) = 0;

	Pos getPos() const noexcept { return pos; }
	WH getWH() const noexcept { return wh; }

   protected:
	GUI& parent;

	Pos pos;
	WH wh;
};
