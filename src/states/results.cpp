#include <3dstris/states/mainmenu.hpp>
#include <3dstris/states/results.hpp>
#include <algorithm>

Results::Results(Ingame* parent)
	: State(),
	  deadText("Game Over"),
	  parent(parent),
	  restartButton(gui.add<Button>(-1, BSCREEN_HEIGHT / 3.0f - 10, 150, 60,
									"Restart", Button::Flags::HCENTER)),
	  menuButton(gui.add<Button>(-1, BSCREEN_HEIGHT - 45 - 10, 100, 45, "Menu",
								 Button::Flags::HCENTER)) {
	deadText.setScale({2, 2});
	deadText.align(Text::Align::SCREEN_CENTER);
}

Results::Results(Ingame* parent, double sprintTime) : Results(parent) {
	deadText.setText(sdscatprintf(sdsempty(), "Time: %.3fs", sprintTime));
	deadText.setScale({1.3f, 1.3f});
	deadText.align(Text::Align::SCREEN_CENTER);
}

void Results::update(double dt) {
	gui.update(dt);

	if (restartButton.pressed()) {
		parent->reset();
		this->game.popState(false, true);
		return;
	}

	if (menuButton.pressed()) {
		this->game.setState(make_unique<MainMenu>());
	}
}

void Results::draw(bool bottom) {
	if (!bottom) {
		parent->draw(bottom);
		C2D_DrawRectSolid(0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, RESULTS);

		deadText.draw();
	} else {
		C2D_TargetClear(this->game.getBottom(), BACKGROUND);

		gui.draw();
	}
}
