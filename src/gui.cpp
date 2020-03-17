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
	C2D_DrawRectSolid(pos.x - scale, pos.y, depth, scale, wh.y, color);

	C2D_DrawRectSolid(pos.x + wh.x, pos.y, depth, scale, wh.y, color);
	C2D_DrawRectSolid(pos.x - scale, pos.y + wh.y, depth, wh.x + 2 * scale,
					  scale, color);
}

void GUI::drawHLine(const Pos pos, const float w, const float scale,
					const Color color, const float depth) noexcept {
	C2D_DrawRectSolid(pos.x - scale, pos.y - scale, depth, w + 2 * scale, scale,
					  color);
}

void GUI::drawVLine(const Pos pos, const float h, const float scale,
					const Color color, const float depth) noexcept {
	C2D_DrawRectSolid(pos.x - scale, pos.y - scale, depth, scale, h + 2 * scale,
					  color);
}
