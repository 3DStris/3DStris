#include <3dstris/gui.hpp>
#include <3dstris/gui/slider.hpp>
#include <algorithm>

Slider::Slider(GUI& parent, float x, float y, float w, float h, float ballSize)
	: Widget(parent), x(x), y(y), w(w), h(h), ballSize(ballSize) {
	pressed = false;
	value = 0.0f;
}

void Slider::draw() const {
	C2D_DrawRectSolid(x, y - h / 2.0f, 0, w, h, parent.primaryCol);
	C2D_DrawEllipseSolid(x + value * w - ballSize / 2.0f, y - ballSize / 2.0f,
						 0, ballSize, ballSize,
						 pressed ? parent.pressedCol : parent.primaryCol);
}

void Slider::update(touchPosition touch, touchPosition) {
	bool down = hidKeysDown() & KEY_TOUCH;
	bool up = hidKeysUp() & KEY_TOUCH;
	if (up)
		pressed = false;
	else if (down && inside(touch.px, touch.py))
		pressed = true;
	if (pressed) {
		value = (float(touch.px) - x) / w;
		value = std::min(1.0f, std::max(0.0f, value));
	}
}

bool Slider::inside(float posX, float posY) const {
	float ballY = y - ballSize / 2.0f;
	return posX >= x && posX <= x + w &&  //
		   posY > ballY && posY < ballY + ballSize;
}

float Slider::getValue() const {
	return value;
}

void Slider::setValue(float v) {
	value = v;
}
