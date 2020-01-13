#include <3dstris/states/mainmenu.hpp>
#include <3dstris/states/sprintresults.hpp>
#include <3dstris/states/sprinttimes.hpp>

SprintResults::SprintResults(Ingame* parent, const SavedGame& saved)
	: State(),
	  timeText(sdscatprintf(sdsempty(), "Time: %.3fs", saved.time)),
	  parent(parent),
	  restartButton(gui.add<Button>(Pos{-1, -1}, WH{150, 60}, "Restart",
									Button::Flags::CENTER)),
	  menuButton(gui.add<Button>(Pos{-1, BSCREEN_HEIGHT - 45 - 10}, WH{100, 45},
								 "Menu", Button::Flags::HCENTER)),
	  timesButton(gui.add<Button>(Pos{-1, 15}, WH{80, 40}, "Times",
								  Button::Flags::HCENTER)) {
	timeText.setScale({1.3f, 1.3f});
	timeText.align(Text::Align::SCREEN_CENTER);

	game.getGames().push(saved);
	game.getGames().save();
}

void SprintResults::update(const double dt) {
	gui.update(dt);

	if (timesButton.pressed()) {
		this->game.pushState(make_unique<SprintTimes>());
		return;
	}

	if (restartButton.pressed()) {
		parent->reset();
		this->game.popState(false, true);
		return;
	}

	if (menuButton.pressed()) {
		this->game.setState(make_unique<MainMenu>());
	}
}

void SprintResults::draw(const bool bottom) {
	if (!bottom) {
		parent->draw(bottom);
		C2D_DrawRectSolid(0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, RESULTS);

		timeText.draw();
	} else {
		C2D_TargetClear(this->game.getBottom(), BACKGROUND);

		gui.draw();
	}
}
