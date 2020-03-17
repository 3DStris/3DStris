#include <3dstris/gui.hpp>

Button::Button(GUI& _parent, const Pos _pos, const WH _wh, sds text,
			   const Flags flags) noexcept
	: Widget(_parent, _pos, _wh), text() {
	if (flags == Flags::HCENTER || flags == Flags::CENTER) {
		pos.x = (parent.getWidth() - wh.x) / 2.0f;
	}
	if (flags == Flags::VCENTER || flags == Flags::CENTER) {
		pos.y = (parent.getHeight() - wh.y) / 2.0f;
	}

	setText(text);
}

Button::Button(GUI& _parent, const Pos _pos, const WH _wh,
			   const char* __restrict text, const Flags flags) noexcept
	: Button::Button(_parent, _pos, _wh, sdsnew(text), flags) {}

void Button::setText(sds text) noexcept {
	this->text.setText(text);

	this->text.scale(wh.x, 0.7f);
	this->text.align(Text::Align::CENTER, Pos{pos.x, pos.y}, WH{wh.x, wh.y});
}

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
