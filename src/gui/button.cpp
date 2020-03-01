#include <3dstris/gui.hpp>

Button::Button(GUI& _parent, const Pos _pos, const WH _wh, sds text,
			   const Flags flags)
	: Widget(_parent, _pos, _wh),
	  text(sdsempty(), Pos{}, {1, 1}, parent.textCol) {
	if (flags == HCENTER || flags == CENTER) {
		pos.x = (parent.getWidth() - wh.x) / 2.0f;
	}
	if (flags == VCENTER || flags == CENTER) {
		pos.y = (parent.getHeight() - wh.y) / 2.0f;
	}

	this->text.setColor(parent.textCol);

	setText(text);
}

Button::Button(GUI& _parent, const Pos _pos, const WH _wh,
			   const char* __restrict text, const Flags flags)
	: Button::Button(_parent, _pos, _wh, sdsnew(text), flags) {}

void Button::setText(sds text) {
	this->text.setText(text);

	this->text.scale(wh.x, 0.7f);
	this->text.align(Text::Align::CENTER, Pos{pos.x, pos.y}, WH{wh.x, wh.y});
}

void Button::draw() const {
	C2D_DrawRectSolid(pos.x, pos.y, 0, wh.x, wh.y,
					  held ? parent.pressedCol : parent.primaryCol);
	GUI::drawOutline(pos, wh, 2, parent.outlineCol);

	text.draw();
}

void Button::update(const touchPosition touch, const touchPosition previous) {
	held = inside(touch.px, touch.py);
	_pressed = inside(previous.px, previous.py) && hidKeysUp() & KEY_TOUCH;
}

bool Button::inside(const float x, const float y) const noexcept {
	return x > pos.x && x < pos.x + wh.x &&  //
		   y > pos.y && y < pos.y + wh.y;
}

bool Button::pressed() {
	return _pressed;
}
