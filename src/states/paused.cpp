#include <3dstris/states/mainmenu.hpp>
#include <3dstris/states/paused.hpp>
#include <algorithm>

Paused::Paused()
	: State(),
	  gui(BSCREEN_WIDTH, BSCREEN_HEIGHT, C2D_Color32(100, 100, 100, 255), WHITE,
		  C2D_Color32(50, 50, 50, 255)),
	  pausedText("Paused", WHITE) {
	pausedText.setScale({2, 2});
	pausedText.setPos({(SCREEN_WIDTH - pausedText.getWH().x) / 2,
					   (SCREEN_HEIGHT - pausedText.getWH().y) / 2});
	unpauseButton =
		gui.addButton(ButtonFlags::CENTER, -1, 10, 200, 115, "Unpause");
	menuButton = gui.addButton(ButtonFlags::HCENTER, -1,
							   BSCREEN_HEIGHT - 40 - 10, 100, 45, "Menu");
	colBackground = C2D_Color32(34, 34, 34, 255);
}

void Paused::update(double dt) {
	gui.update(dt);

	auto kDown = hidKeysDown();
	if (unpauseButton->pressed() || (kDown > KEY_A && kDown <= KEY_ZR)) {
		this->game.popState(false, true);
		return;
	}

	if (menuButton->pressed()) {
		this->game.setState(make_unique<MainMenu>());
	}
}

void Paused::draw(bool bottom) {
	if (!bottom) {
		C2D_TargetClear(this->game.getTop(), colBackground);

		pausedText.draw();
	} else {
		C2D_TargetClear(this->game.getBottom(), colBackground);

		gui.draw();
	}
}
