#pragma once

#include <3dstris/gui/button.hpp>
#include <3dstris/gui/doubleinputfield.hpp>
#include <3dstris/gui/widget.hpp>
#include <3dstris/util.hpp>
#include <vector>

enum ButtonFlags { NONE, HCENTER, VCENTER, CENTER };

class GUI {
   public:
	GUI(int width = BSCREEN_WIDTH, int height = BSCREEN_HEIGHT,
		Color primaryCol = BUTTON, Color textCol = WHITE,
		Color pressedCol = BUTTON_HELD, Color borderCol = BUTTON_BORDER);

	template <typename T>
	Button& addButton(float x, float y, float w, float h, const T text) {
		widgets.push_back(make_unique<Button>(*this, x, y, w, h, text));
		return static_cast<Button&>(*widgets.back());
	}

	template <typename T>
	Button& addButton(ButtonFlags flags, float x, float y, float w, float h,
					  const T text) {
		if (flags == ButtonFlags::HCENTER || flags == ButtonFlags::CENTER)
			x = width / 2.0f - w / 2.0f;
		if (flags == ButtonFlags::VCENTER || flags == ButtonFlags::CENTER)
			y = height / 2.0f - h / 2.0f;
		return this->addButton(x, y, w, h, text);
	}

	template <typename T>
	DoubleInputField& addFloatInputField(float x, float y, float w, float h,
										const T suffix = sdsempty()) {
		widgets.push_back(
			make_unique<DoubleInputField>(*this, x, y, w, h, suffix));
		return static_cast<DoubleInputField&>(*widgets.back());
	}

	void update(double dt);
	void draw();

	static void drawOutline(float x, float y, float w, float h, u8 scale = 2,
							Color color = BUTTON_BORDER);

	Color primaryCol, textCol, pressedCol, borderCol;

   private:
	int width, height;
	std::vector<std::unique_ptr<Widget>> widgets;
	touchPosition previousTouch;
};
