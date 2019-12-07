#pragma once

#include <3dstris/gui/button.hpp>
#include <3dstris/util.hpp>
#include <functional>
#include <vector>

enum ButtonFlags { NONE = 0, HCENTER = 1, VCENTER = 2 };

class GUI {
   public:
	GUI(int width, int height, Color primaryCol, Color textCol,
		Color pressedCol);

	void addButton(Button& button);
	void addButton(float x, float y, float w, float h, const char* text,
				   std::function<void()> onPress);
	void addButton(ButtonFlags flags, float x, float y, float w, float h,
				   const char* text, std::function<void()> onPress);

	void update(double dt);
	void draw();

	Color primaryCol, textCol, pressedCol;

   private:
	int width, height;
	std::vector<Button> buttons;
	touchPosition previousTouch;
};
