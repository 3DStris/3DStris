#pragma once

#include <3dstris/gui/button.hpp>
#include <3dstris/gui/slider.hpp>
#include <3dstris/gui/widget.hpp>
#include <3dstris/util.hpp>
#include <functional>
#include <memory>
#include <vector>

enum ButtonFlags { NONE, HCENTER, VCENTER, CENTER };

class GUI {
   public:
	GUI(int width, int height, Color primaryCol, Color textCol,
		Color pressedCol);

	template <typename T>
	std::shared_ptr<Button> addButton(float x, float y, float w, float h,
									  const T text) {
		auto button = std::make_shared<Button>(*this, x, y, w, h, text);
		widgets.push_back(button);
		return button;
	}

	template <typename T>
	std::shared_ptr<Button> addButton(ButtonFlags flags, float x, float y,
									  float w, float h, const T text) {
		if (flags == ButtonFlags::HCENTER || flags == ButtonFlags::CENTER)
			x = width / 2.0f - w / 2.0f;
		if (flags == ButtonFlags::VCENTER || flags == ButtonFlags::CENTER)
			y = height / 2.0f - h / 2.0f;
		return this->addButton(x, y, w, h, text);
	}

	std::shared_ptr<Slider> addSlider(float x, float y, float w, float h,
									  float ballSize);

	void addButton(float x, float y, float w, float h, const char* text,
				   std::function<void()> onPress);
	void addButton(ButtonFlags flags, float x, float y, float w, float h,
				   const char* text, std::function<void()> onPress);

	Slider& addSlider(float x, float y, float w, float h, float ballSize);

	void update(double dt);
	void draw();

	Color primaryCol, textCol, pressedCol;

   private:
	int width, height;
	std::vector<std::shared_ptr<Widget>> widgets;
	touchPosition previousTouch;
};
