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

void GUI::drawOutline(float x, float y, float w, float h, u8 scale,
					  Color color) {
	C2D_DrawRectSolid(x - scale, y - scale, 0.5f, w + 2 * scale, scale, color);
	C2D_DrawRectSolid(x - scale, y, 0.5f, scale, h, color);
	C2D_DrawRectSolid(x + w, y, 0.5f, scale, h, color);
	C2D_DrawRectSolid(x - scale, y + h, 0.5f, w + 2 * scale, scale, color);
}
