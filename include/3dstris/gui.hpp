#pragma once

#include <vector>
#include <functional>
#include <3dstris/gui/button.hpp>
#include <3dstris/util.hpp>

enum ButtonFlags {NONE = 0, HCENTER = 1, VCENTER = 2};

class GUI {
public:
	Color primaryCol, textCol, pressedCol;

	GUI(int width, int height, Color primaryCol, Color textCol, Color pressedCol);

	void addButton(float x, float y, float w, float h, const char* text, std::function<void()> onPress);
	void addButton(ButtonFlags flags, float x, float y, float w, float h, const char* text, std::function<void()> onPress);
	
	void update(double dt);
	void draw();
private:
	int width, height;
	std::vector<Button> buttons;
	touchPosition previousTouch;
};