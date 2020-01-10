#include <3dstris/states/mainmenu.hpp>
#include <3dstris/states/paused.hpp>
#include <algorithm>

Paused::Paused(Ingame* parent)
	: State(),
	  pausedText("Paused"),
	  parent(parent),
	  restartButton(
		  gui.addButton(ButtonFlags::HCENTER, -1, 6, 100, 45, "Restart")),
	  unpauseButton(
		  gui.addButton(ButtonFlags::CENTER, -1, 10, 200, 115, "Resume")),
	  menuButton(gui.addButton(ButtonFlags::HCENTER, -1,
							   BSCREEN_HEIGHT - 40 - 10, 100, 45, "Menu")) {
	pausedText.setScale({2, 2});
	pausedText.setPos({(SCREEN_WIDTH - pausedText.getWH().x) / 2,
					   (SCREEN_HEIGHT - pausedText.getWH().y) / 2});
}

void Paused::update(double dt) {
	gui.update(dt);

	auto kDown = hidKeysDown();
	if (restartButton.pressed()) {
        parent->reset();
        this->game.popState(false, true);
        //this->game.setState(make_unique<Playing>(), false, true);
		return;
	}

	if (unpauseButton.pressed() || (kDown > KEY_A && kDown <= KEY_ZR)) {
		this->game.popState(false, true);
		return;
	}

	if (menuButton.pressed()) {
		this->game.setState(make_unique<MainMenu>());
	}
}

void Paused::draw(bool bottom) {
	if (!bottom) {
		parent->draw(bottom);
		C2D_DrawRectSolid(0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, PAUSED);

		pausedText.draw();
	} else {
        C2D_TargetClear(this->game.getBottom(), BACKGROUND);

		gui.draw();
	}
}
