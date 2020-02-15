#include <3dstris/gui.hpp>

Button::Button(GUI& _parent, const Pos _pos, const WH _wh, const sds text,
			   const Flags flags)
	: Widget(_parent, _pos, _wh),
	  text(sdsempty(), Pos{}, {1, 1}, parent.textCol) {
	if (flags == HCENTER || flags == CENTER) {
		pos.x = (parent.getWidth() - wh.x) / 2.0f;
	}
	if (flags == VCENTER || flags == CENTER) {
		pos.y = (parent.getHeight() - wh.y) / 2.0f;
	}

	this->setText(text);
}

Button::Button(GUI& _parent, const Pos _pos, const WH _wh, const char* text,
			   const Flags flags)
	: Button::Button(_parent, _pos, _wh, sdsnew(text), flags) {}

void Button::setText(sds text) {
	this->text.setText(text);
	this->text.setScale({1, 1});

	Vector2 textWH = this->text.getWH();
	// textW and textH are the text size at scale 1:1, do some math to figure
	// out scale that fits on the button
	// 1   textW
	// - = ----
	// x   w-10
	const float textScale = std::min((wh.x - 10) / textWH.x, 0.7f);
	this->text.setScale({textScale, textScale});

	textWH = this->text.getWH();
	// textW should hopefully be w - 10

	this->text.setPos(
		Pos{pos.x + (wh.x - textWH.x) / 2, pos.y + (wh.y - textWH.y) / 2});
	this->text.setColor(parent.textCol);
}

void Button::draw() const {
	C2D_DrawRectSolid(pos.x, pos.y, 0, wh.x, wh.y,
					  held ? parent.pressedCol : parent.primaryCol);
	GUI::drawOutline(pos, wh, 2, parent.outlineCol);

	this->text.draw();
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
