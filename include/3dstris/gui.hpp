#pragma once

#include <3dstris/gui/button.hpp>
#include <3dstris/gui/slider.hpp>
#include <3dstris/util.hpp>
#include <functional>
#include <memory>
#include <vector>

enum ButtonFlags { NONE, HCENTER, VCENTER, CENTER };

class GUI {
   public:
	GUI(int width, int height, Color primaryCol, Color textCol,
		Color pressedCol);

	void addButton(float x, float y, float w, float h, const char* text,
				   std::function<void()> onPress);
	void addButton(ButtonFlags flags, float x, float y, float w, float h,
				   const char* text, std::function<void()> onPress);

	std::shared_ptr<Slider> addSlider(float x, float y, float w, float h, float ballSize);

	void update(double dt);
	void draw();

	Color primaryCol, textCol, pressedCol;

   private:
	int width, height;
	std::vector<std::unique_ptr<Button>> buttons;
	std::vector<std::shared_ptr<Slider>> sliders;
	touchPosition previousTouch;
};
