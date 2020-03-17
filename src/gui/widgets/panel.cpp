#include <3dstris/gui.hpp>
#include <3dstris/gui/widgets/panel.hpp>

Panel::Panel(GUI& _parent, const Pos _pos, const WH _wh, const bool outline,
			 const Color& color, const Color& outlineColor) noexcept
	: Widget(_parent, _pos, _wh),
	  color(color),
	  outlineColor(outlineColor),
	  outline(outline) {}

void Panel::draw() const noexcept {
	C2D_DrawRectSolid(pos.x, pos.y, 0, wh.x, wh.y, color);
	if (outline) {
		GUI::drawOutline(pos, wh, 2, outlineColor);
	}
}
