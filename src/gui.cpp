#include <3dstris/gui.hpp>

GUI::GUI(const u16 width, const u16 height, const Color primaryCol,
		 const Color textCol, const Color pressedCol, const Color outlineCol)
	: primaryCol(primaryCol),
	  textCol(textCol),
	  pressedCol(pressedCol),
	  outlineCol(outlineCol),

	  width(width),
	  height(height) {}

u16 GUI::getWidth() const noexcept {
	return width;
}
u16 GUI::getHeight() const noexcept {
	return height;
}

void GUI::update(double) {
	touchPosition touch;
	hidTouchRead(&touch);

	for (auto& widget : widgets) {
		widget->update(touch, previousTouch);
	}

	previousTouch = touch;
}
void GUI::draw() const {
	for (const auto& widget : widgets) {
		widget->draw();
	}
}

void GUI::drawOutline(const Pos pos, const WH wh, const float scale,
					  const Color color, const float depth) {
	drawHLine(pos, wh.x, scale, color, depth);
	C2D_DrawRectSolid(pos.x - scale, pos.y, depth, scale, wh.y, color);

	C2D_DrawRectSolid(pos.x + wh.x, pos.y, depth, scale, wh.y, color);
	C2D_DrawRectSolid(pos.x - scale, pos.y + wh.y, depth, wh.x + 2 * scale,
					  scale, color);
}

void GUI::drawHLine(const Pos pos, const float w, const float scale,
					const Color color, const float depth) {
	C2D_DrawRectSolid(pos.x - scale, pos.y - scale, depth, w + 2 * scale, scale,
					  color);
}

void GUI::drawVLine(const Pos pos, const float h, const float scale,
					const Color color, const float depth) {
	C2D_DrawRectSolid(pos.x - scale, pos.y - scale, depth, scale, h + 2 * scale,
					  color);
}
