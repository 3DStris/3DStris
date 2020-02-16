#pragma once

#include <3dstris/util.hpp>

class GUI;
class Widget {
   public:
	Widget(GUI& parent, const Pos pos, const WH wh);
	virtual ~Widget() = default;

	Widget(const Widget&) = delete;
	Widget(Widget&&) = delete;
	Widget& operator=(const Widget&) = delete;
	Widget& operator=(Widget&&) = delete;

	virtual void draw() const = 0;
	virtual void update(const touchPosition touch,
						const touchPosition previousTouch) = 0;

	Pos getPos() const noexcept { return pos; }
	WH getWH() const noexcept { return wh; }

   protected:
	GUI& parent;

	Pos pos;
	WH wh;
};
