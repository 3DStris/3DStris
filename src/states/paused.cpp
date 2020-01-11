#include <3dstris/states/mainmenu.hpp>
#include <3dstris/states/paused.hpp>
#include <algorithm>

Paused::Paused(State* parent)
	: State(),
	  pausedText("Paused"),
	  parent(parent),
	  restartButton(
		  gui.add<Button>(-1, 6, 100, 45, "Restart", Button::Flags::HCENTER)),
	  unpauseButton(
		  gui.add<Button>(-1, 10, 200, 115, "Resume", Button::Flags::CENTER)),
	  menuButton(gui.add<Button>(-1, BSCREEN_HEIGHT - 40 - 10, 100, 45, "Menu",
								 Button::Flags::HCENTER)) {
	pausedText.setScale({2, 2});
	pausedText.align(Text::Align::SCREEN_CENTER);
}

void Paused::update(double dt) {
	gui.update(dt);

	auto kDown = hidKeysDown();
	if (restartButton.pressed()) {
		this->game.setState(make_unique<Playing>(), false, true);
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
