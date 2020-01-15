#include <3dstris/gui.hpp>

GUI::GUI(int width, int height, Color primaryCol, Color textCol,
		 Color pressedCol, Color outlineCol)
	: primaryCol(primaryCol),
	  textCol(textCol),
	  pressedCol(pressedCol),
	  outlineCol(outlineCol),
	  width(width),
	  height(height) {}

int GUI::getWidth() const noexcept {
	return width;
}

int GUI::getHeight() const noexcept {
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

void GUI::draw() {
	for (const auto& widget : widgets) {
		widget->draw();
	}
}

void GUI::drawOutline(const Pos pos, const WH wh, const float scale,
					  const Color color) {
	C2D_DrawRectSolid(pos.x - scale, pos.y - scale, 0.1f, wh.x + 2 * scale,
					  scale, color);
	C2D_DrawRectSolid(pos.x - scale, pos.y, 0.1f, scale, wh.y, color);
	C2D_DrawRectSolid(pos.x + wh.x, pos.y, 0.1f, scale, wh.y, color);
	C2D_DrawRectSolid(pos.x - scale, pos.y + wh.y, 0.1f, wh.x + 2 * scale,
					  scale, color);
}

void GUI::drawHLine(const Pos pos, const float w, const float scale,
					const Color color) {
	C2D_DrawRectSolid(pos.x - scale, pos.y - scale, 0.5f, w + 2 * scale, scale,
					  color);
}

void GUI::drawVLine(const Pos pos, const float h, const float scale,
					const Color color) {
	C2D_DrawRectSolid(pos.x - scale, pos.y - scale, 0.5f, scale, h + 2 * scale,
					  color);
}
