#include <3dstris/sprites.h>
#include <3dstris/states/configfailed.hpp>
#include <3dstris/util.hpp>
#include <3dstris/version.hpp>

ConfigFailed::ConfigFailed()
	: State(),
	  failedText("Failed to load config; your settings have been reset.",
				 WHITE),
	  gui(BSCREEN_WIDTH, BSCREEN_HEIGHT, C2D_Color32(100, 100, 100, 255), WHITE,
		  C2D_Color32(50, 50, 50, 255)) {
	colBackground = C2D_Color32(34, 34, 34, 255);

	failedText.setPos({(SCREEN_WIDTH - failedText.getWH().x) / 2,
					   (SCREEN_HEIGHT - failedText.getWH().y) / 2});

	gui.addButton(ButtonFlags::CENTER, -1, -1, SCREEN_WIDTH - 100,
				  SCREEN_HEIGHT - 100, "OK",
				  [this]() { this->game.setState(make_unique<MainMenu>()); });
}

void ConfigFailed::update(double dt) {
	gui.update(dt);
}

void ConfigFailed::draw(bool bottom) {
	if (!bottom) {
		C2D_TargetClear(this->game.getTop(), colBackground);

		failedText.draw();
	} else {
		C2D_TargetClear(this->game.getBottom(), colBackground);

		gui.draw();
	}
}
