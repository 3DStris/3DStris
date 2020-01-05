#pragma once

#include <3ds.h>

class GUI;
class Widget {
   public:
	Widget(GUI& parent);
	virtual ~Widget() = default;

	Widget(const Widget&) = delete;
	Widget(Widget&&) = delete;
	Widget& operator=(const Widget&) = delete;
	Widget& operator=(Widget&&) = delete;

	virtual void draw() const = 0;
	virtual void update(touchPosition touch, touchPosition previousTouch) = 0;

   protected:
	GUI& parent;
};
