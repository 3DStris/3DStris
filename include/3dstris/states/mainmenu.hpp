#pragma once

#include <citro2d.h>
#include <3dstris/state.hpp>
#include <3dstris/util.hpp>
#include <3dstris/gui.hpp>

class MainMenu : public State {
public:
	MainMenu(Game& game);

	void update(double dt);
	void draw(bool bottom);

private:
	C2D_Text titleText;
	Color titleTextColor;
	Color bgColor;

	GUI gui;
};