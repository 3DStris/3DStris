#include <3dstris/gui.hpp>

Button::Button(GUI& parent, float x, float y, float w, float h, const sds text)
	: Widget(parent), text(sdsempty(), parent.textCol), x(x), y(y), w(w), h(h) {
	this->setText(text);
}

Button::Button(GUI& parent, float x, float y, float w, float h,
			   const char* text)
	: Button::Button(parent, x, y, w, h, sdsnew(text)) {}

void Button::setText(const sds text) {
	this->text.setText(text);

	auto textWH = this->text.getWH();
	// textW and textH are the text size at scale 1:1, do some math to figure
	// out scale that fits on the button
	// 1   textW
	// - = ----
	// x   w-10
	auto textScale = std::min((w - 10) / textWH.x, 0.7f);

	this->text.setScale({textScale, textScale});

	textWH = this->text.getWH();
	// textW should hopefully be w - 10

	this->text.setPos({x + (w - textWH.x) / 2.0f, y + (h - textWH.y) / 2.0f});
	this->text.setColor(parent.textCol);
}

void Button::draw() const {
	C2D_DrawRectSolid(x, y, 0, w, h,
					  held ? parent.pressedCol : parent.primaryCol);
	GUI::drawOutline(x, y, w, h);
	this->text.draw();
}

void Button::update(touchPosition touch, touchPosition previous) {
	held = inside(touch.px, touch.py);
	_pressed =
		inside(previous.px, previous.py) && touch.px == 0 && touch.py == 0;
}

bool Button::inside(float posX, float posY) const {
	return posX > x && posX < x + w &&  //
		   posY > y && posY < y + h;
}

bool Button::pressed() {
	return _pressed;
}
