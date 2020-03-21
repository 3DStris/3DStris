#include <3dstris/states/game/sprintresults.hpp>
#include <3dstris/states/menu/mainmenu.hpp>
#include <3dstris/states/menu/sprinttimes.hpp>

SprintResults::SprintResults(Ingame* parent, SavedGame&& saved)
	: State(),
	  parent(parent),

	  timeFormat(game.translate("results.sprint.time")),
	  timeText(String::fromPrintf(timeFormat, saved.time)),

	  restart(gui.add<Button>(Pos{}, WH{150, 60},
							  game.translate("results.restart"),
							  Button::Flags::CENTER)),
	  times(gui.add<Button>(Pos{0, 15}, WH{80, 40},
							game.translate("results.sprint.times"),
							Button::Flags::HCENTER)),
	  menu(gui.add<Button>(Pos(0, gui.getHeight() - 45 - 10), WH{100, 45},
						   game.translate("menu"), Button::Flags::HCENTER)) {
	timeText.setScale({1.3f, 1.3f});
	timeText.align(Text::Align::SCREEN_CENTER);

	game.getGames().push(std::move(saved));
	game.getGames().save();
}

void SprintResults::update(const double dt) {
	gui.update(dt);

	if (times.pressed()) {
		game.pushState(make_unique<SprintTimes>());
	} else if (restart.pressed()) {
		parent->reset();
		game.popState(false, true);
	} else if (menu.pressed() || hidKeysDown() & KEY_B) {
		game.setState(make_unique<MainMenu>());
	}
}

void SprintResults::draw(const bool bottom) const {
	if (!bottom) {
		parent->draw(bottom);
		C2D_DrawRectSolid(0, 0, 1, SCREEN_WIDTH, SCREEN_HEIGHT, RESULTS);

		timeText.draw();
	} else {
		C2D_TargetClear(game.getBottom(), gui.getTheme().background);

		gui.draw();
	}
}
