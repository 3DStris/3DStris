#include <3dstris/states/mainmenu.hpp>
#include <3dstris/states/results.hpp>
#include <algorithm>

Results::Results(Ingame* parent)
	: State(),
	  parent(parent),

	  deadText("Game Over"),

	  restartButton(gui.add<Button>(Pos{-1, BSCREEN_HEIGHT / 3.0f - 10},
									WH{150, 60}, "Restart",
									Button::Flags::HCENTER)),
	  menuButton(gui.add<Button>(Pos{-1, BSCREEN_HEIGHT - 45 - 10}, WH{100, 45},
								 "Menu", Button::Flags::HCENTER)) {
	deadText.setScale({2, 2});
	deadText.align(Text::Align::SCREEN_CENTER);
}

Results::Results(Ingame* parent, SavedGame&& saved) : Results(parent) {
	deadText.setText(sdscatprintf(sdsempty(), "Time: %.3fs", saved.time));
	deadText.setScale({1.3f, 1.3f});
	deadText.align(Text::Align::SCREEN_CENTER);

	game.getGames().push(std::move(saved));
	game.getGames().save();
}

void Results::update(const double dt) {
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

void Results::draw(const bool bottom) {
	if (!bottom) {
		parent->draw(bottom);
		C2D_DrawRectSolid(0, 0, 1, SCREEN_WIDTH, SCREEN_HEIGHT, RESULTS);

		deadText.draw();
	} else {
		C2D_TargetClear(this->game.getBottom(), BACKGROUND);

		gui.draw();
	}
}
