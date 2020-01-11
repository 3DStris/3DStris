#include <3dstris/gui.hpp>

Panel::Panel(GUI& _parent, const Vector2 _pos, const Vector2 _wh, bool outline,
			 const Color col, const Color outlineCol)
	: Widget(_parent, _pos, _wh),
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
