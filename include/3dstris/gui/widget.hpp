#pragma once

extern "C" {
// clang-format off
// fucking thanks ctrulib
#include <3ds/types.h>
#include <3ds/services/hid.h>
// clang-format on
}

#include <3dstris/util/math.hpp>

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
