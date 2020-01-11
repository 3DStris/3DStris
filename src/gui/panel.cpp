#include <3dstris/gui.hpp>
#include <3dstris/gui/panel.hpp>

Panel::Panel(GUI& _parent, const Vector2 _pos, const Vector2 _wh,
			 const bool outline, const Color col, const Color outlineCol)
	: Widget(_parent, _pos, _wh),
	  col(col),
	  outlineCol(outlineCol),
	  outline(outline) {}

void Panel::draw() const {
	C2D_DrawRectSolid(pos.x, pos.y, 0, wh.x, wh.y, col);
	if (outline) {
		GUI::drawOutline(pos, wh, 2, outlineCol);
	}
}

void Panel::update(touchPosition, touchPosition) {}
