#include <3dstris/gui/widgets/button.hpp>

void Button::draw() const noexcept {
	C2D_DrawRectSolid(
		pos.x, pos.y, 0, wh.x, wh.y,
		held ? parent.getTheme().buttonHeld : parent.getTheme().button);
	GUI::drawOutline(pos, wh, 2, parent.getTheme().buttonOutline);

	text.draw();
}

void Button::update(const touchPosition touch, const touchPosition previous) {
	held = inside(touch.px, touch.py);
	_pressed = inside(previous.px, previous.py) && hidKeysUp() & KEY_TOUCH;
}

bool Button::inside(const float x, const float y) const noexcept {
	return x > pos.x && x < pos.x + wh.x &&	 //
		   y > pos.y && y < pos.y + wh.y;
}

bool Button::pressed() noexcept {
	return _pressed;
}
