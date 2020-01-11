#include <3dstris/gui.hpp>

Panel::Panel(GUI& parent, float x, float y, float w, float h, bool outline,
			 const Color col, const Color outlineCol)
	: Widget(parent, {x, y}, {w, h}),
	  col(col),
	  outlineCol(outlineCol),
	  outline(outline) {}

void Panel::draw() const {
	C2D_DrawRectSolid(pos.x, pos.y, 0, wh.x, wh.y, col);
	if (outline) {
		GUI::drawOutline(pos.x, pos.y, wh.x, wh.y, 2, outlineCol);
	}
}

void Panel::update(touchPosition, touchPosition) {}
