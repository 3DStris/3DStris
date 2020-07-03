#include <3dstris/gui.hpp>

GUI::GUI(const u32 width, const u32 height) noexcept
	: width(width), height(height) {}

u32 GUI::getWidth() const noexcept {
	return width;
}
u32 GUI::getHeight() const noexcept {
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

const Theme& GUI::getTheme() noexcept {
	return Game::get().getTheme();
}

void GUI::drawOutline(const Pos pos, const WH wh, const float scale,
					  const Color color, const float depth) noexcept {
	drawHLine(pos, wh.x, scale, color, depth);
	drawVLine(pos, wh.y, scale, color, depth);

	drawHLine({pos.x, pos.y + wh.y}, wh.x, scale, color, depth);
	drawVLine({pos.x + wh.x, pos.y}, wh.y, scale, color, depth);
}

void GUI::drawHLine(const Pos pos, const float w, const float scale,
					const Color color, const float depth) noexcept {
	C2D_DrawRectSolid(pos.x, pos.y, depth, w + scale, scale, color);
}

void GUI::drawVLine(const Pos pos, const float h, const float scale,
					const Color color, const float depth) noexcept {
	C2D_DrawRectSolid(pos.x, pos.y, depth, scale, h + scale, color);
}
