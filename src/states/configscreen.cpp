#include <3dstris/sprites.h>
#include <3dstris/gui/inputfield.hpp>
#include <3dstris/states/configscreen.hpp>
#include <3dstris/util.hpp>
#include <3dstris/version.hpp>

ConfigScreen::ConfigScreen()
	: State(),
	  gui(BSCREEN_WIDTH, BSCREEN_HEIGHT, C2D_Color32(100, 100, 100, 255), WHITE,
		  C2D_Color32(50, 50, 50, 255)) {
	colBackground = C2D_Color32(34, 34, 34, 255);

	gui.addInputField(1, 1, 50, 10, 1);
}

void ConfigScreen::update(double dt) {
	gui.update(dt);
}

void ConfigScreen::draw(bool bottom) {
	if (!bottom) {
		C2D_TargetClear(this->game.getTop(), colBackground);
	} else {
		C2D_TargetClear(this->game.getBottom(), colBackground);

		gui.draw();
	}
}
