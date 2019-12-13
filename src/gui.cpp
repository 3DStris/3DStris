#include <3dstris/gui.hpp>

GUI::GUI(int width, int height, Color primaryCol, Color textCol,
		 Color pressedCol)
	: primaryCol(primaryCol),
	  textCol(textCol),
	  pressedCol(pressedCol),
	  width(width),
	  height(height) {}

void GUI::addButton(float x, float y, float w, float h, const char* text,
					std::function<void()> onPress) {
	buttons.emplace_back(*this, x, y, w, h, text, onPress);
}

void GUI::addButton(ButtonFlags flags, float x, float y, float w, float h,
					const char* text, std::function<void()> onPress) {
	if (flags == ButtonFlags::HCENTER || flags == ButtonFlags::CENTER)
		x = width / 2.0f - w / 2.0f;
	if (flags == ButtonFlags::VCENTER || flags == ButtonFlags::CENTER)
		y = height / 2.0f - h / 2.0f;
	this->addButton(x, y, w, h, text, onPress);
}

std::shared_ptr<Slider> GUI::addSlider(float x, float y, float w, float h, float ballSize) {
	auto slider = std::make_shared<Slider>(*this, x, y, w, h, ballSize);
	sliders.push_back(slider);
	return slider;
}

void GUI::update(double) {
	touchPosition touch;
	hidTouchRead(&touch);

	for (auto& button : buttons) {
		button.update(touch);
		if (button.inside(previousTouch.px, previousTouch.py) &&
			touch.px == 0 && touch.py == 0) {
			button.press();
		}
	}
	for (auto& slider : sliders) {
		slider->update(touch);
	}

	previousTouch = touch;
}

void GUI::draw() {
	for (const auto& button : buttons) {
		button.draw();
	}
	for (const auto& slider : sliders) {
		slider->draw();
	}
}
