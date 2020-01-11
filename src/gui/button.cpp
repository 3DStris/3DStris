#include <3dstris/gui.hpp>

Button::Button(GUI& parent, float x, float y, float w, float h, const sds text,
			   Flags flags)
	: Widget(parent, {x, y}, {w, h}), text(sdsempty(), parent.textCol) {
	if (flags == Flags::HCENTER || flags == Flags::CENTER) {
		pos.x = (parent.getWidth() - w) / 2.0f;
	}
	if (flags == Flags::VCENTER || flags == Flags::CENTER) {
		pos.y = (parent.getHeight() - h) / 2.0f;
	}
	this->setText(text);
}

Button::Button(GUI& parent, float x, float y, float w, float h,
			   const char* text, Flags flags)
	: Button::Button(parent, x, y, w, h, sdsnew(text), flags) {}

void Button::setText(const sds text) {
	this->text.setText(text);

	auto textWH = this->text.getWH();
	// textW and textH are the text size at scale 1:1, do some math to figure
	// out scale that fits on the button
	// 1   textW
	// - = ----
	// x   w-10
	auto textScale = std::min((wh.x - 10) / textWH.x, 0.7f);

	this->text.setScale({textScale, textScale});

	textWH = this->text.getWH();
	// textW should hopefully be w - 10

	this->text.setPos(
		{pos.x + (wh.x - textWH.x) / 2.0f, pos.y + (wh.y - textWH.y) / 2.0f});
	this->text.setColor(parent.textCol);
}

void Button::draw() const {
	C2D_DrawRectSolid(pos.x, pos.y, 0, wh.x, wh.y,
					  held ? parent.pressedCol : parent.primaryCol);
	GUI::drawOutline(pos.x, pos.y, wh.x, wh.y, 2, parent.outlineCol);
	this->text.draw();
}

void Button::update(touchPosition touch, touchPosition previous) {
	held = inside(touch.px, touch.py);
	_pressed = inside(previous.px, previous.py) && hidKeysUp() & KEY_TOUCH;
}

bool Button::inside(float posX, float posY) const {
	return posX > pos.x && posX < pos.x + wh.x &&  //
		   posY > pos.y && posY < pos.y + wh.y;
}

bool Button::pressed() {
	return _pressed;
}
