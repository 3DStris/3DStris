#include <3dstris/gui.hpp>
#include <3dstris/gui/button.hpp>

Button::Button(GUI& parent, float x, float y, float w, float h,
			   const char* text, std::function<void()> onPress)
	: parent(parent), x(x), y(y), w(w), h(h), onPress(onPress) {
	textBuf = C2D_TextBufNew(strlen(text));

	this->setText(text);
}

Button::~Button() {
	C2D_TextBufDelete(textBuf);
}

void Button::setText(const char* text, bool resizeBuf) {
	if (resizeBuf) {
		C2D_TextBufClear(textBuf);
		C2D_TextBufResize(textBuf, strlen(text));
	}

	C2D_TextParse(&this->text, textBuf, text);
	C2D_TextOptimize(&this->text);

	C2D_TextGetDimensions(&this->text, 1, 1, &textW, &textH);

	// textW and textH are the text size at scale 1:1, do some math to figure
	// out scale that fits on the button
	// 1   textW
	// - = ----
	// x   w-10
	textSX = std::min((w - 10) / textW, 1.0f);
	textSY = textSX;  // pray that the button isn't taller than it is wider

	C2D_TextGetDimensions(&this->text, textSX, textSY, &textW, &textH);
	// textW should hopefully be w - 10
}

void Button::draw() const {
	C2D_DrawRectSolid(x, y, 0, w, h,
					  pressed ? parent.pressedCol : parent.primaryCol);
	C2D_DrawText(&text, C2D_WithColor, x + (w - textW) / 2.0f,
				 y + (h - textH) / 2.0f, 0, textSX, textSY, parent.textCol);
}

void Button::update(touchPosition touch) {
	pressed = inside(touch.px, touch.py);
}

bool Button::inside(float posX, float posY) const {
	return posX > x && posX < x + w &&  //
		   posY > y && posY < y + h;
}

void Button::press() {
	onPress();
}
