#include <3dstris/gui.hpp>

GUI::GUI(int width, int height, Color primaryCol, Color textCol,
		 Color pressedCol)
	: primaryCol(primaryCol),
	  textCol(textCol),
	  pressedCol(pressedCol),
	  width(width),
	  height(height) {
	return;
}

void GUI::addButton(Button& button) {
	buttons.push_back(button);
}

void GUI::addButton(float x, float y, float w, float h, const char* text,
					std::function<void()> onPress) {
	buttons.push_back(Button(*this, x, y, w, h, text, onPress));
}

void GUI::addButton(ButtonFlags flags, float x, float y, float w, float h,
					const char* text, std::function<void()> onPress) {
	if (flags & ButtonFlags::HCENTER)
		x = width / 2.0f - w / 2.0f;
	if (flags & ButtonFlags::VCENTER)
		y = height / 2.0f - h / 2.0f;
	this->addButton(x, y, w, h, text, onPress);
}

void GUI::update(double) {
	touchPosition touch;
	hidTouchRead(&touch);

	for (Button& button : buttons) {
		button.update(touch);
		if (button.inside(previousTouch.px, previousTouch.py) &&
			touch.px == 0 && touch.py == 0) {
			button.press();
		}
	}

	previousTouch = touch;
}

void GUI::draw() {
	for (const Button& button : buttons) {
		button.draw();
	}
}
