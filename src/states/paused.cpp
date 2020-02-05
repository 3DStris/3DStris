#include <3dstris/states/mainmenu.hpp>
#include <3dstris/states/paused.hpp>
#include <algorithm>

Paused::Paused(Ingame* parent)
	: State(),
	  pausedText(game.translate("paused.title")),
	  parent(parent),
	  restartButton(gui.add<Button>(Pos{-1, 6}, WH{100, 45},
									game.translate("results.restart"),
									Button::Flags::HCENTER)),
	  unpauseButton(gui.add<Button>(Pos{-1, 10}, WH{200, 115},
									game.translate("paused.resume"),
									Button::Flags::CENTER)),
	  menuButton(gui.add<Button>(Pos{-1, BSCREEN_HEIGHT - 40 - 10}, WH{100, 45},
								 game.translate("results.menu"),
								 Button::Flags::HCENTER)) {
	pausedText.setScale({2, 2});
	pausedText.align(Text::Align::SCREEN_CENTER);
}

void Paused::update(const double dt) {
	gui.update(dt);

	auto kDown = hidKeysDown();
	if (restartButton.pressed()) {
		parent->reset();
		this->game.popState(false, true);
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

void Paused::draw(const bool bottom) {
	if (!bottom) {
		parent->draw(bottom);
		C2D_DrawRectSolid(0, 0, 1, SCREEN_WIDTH, SCREEN_HEIGHT, PAUSED);

		pausedText.draw();
	} else {
		C2D_TargetClear(this->game.getBottom(), BACKGROUND);

		gui.draw();
	}
}
