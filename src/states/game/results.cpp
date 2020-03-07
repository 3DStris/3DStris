#include <3dstris/states/game/results.hpp>
#include <3dstris/states/menu/mainmenu.hpp>
#include <algorithm>

Results::Results(Ingame* parent)
	: State(),
	  parent(parent),

	  deadText(game.translate("results.dead")),

	  restartButton(gui.add<Button>(
		  Pos{-1, BSCREEN_HEIGHT / 3.0f - 10}, WH{150, 60},
		  game.translate("results.restart"), Button::Flags::HCENTER)),
	  menuButton(gui.add<Button>(Pos{-1, BSCREEN_HEIGHT - 45 - 10}, WH{100, 45},
								 game.translate("menu"),
								 Button::Flags::HCENTER)) {
	deadText.setScale({2, 2});
	deadText.align(Text::Align::SCREEN_CENTER);
}

void Results::update(const double dt) {
	gui.update(dt);

	if (restartButton.pressed()) {
		parent->reset();
		game.popState(false, true);
	}

	if (menuButton.pressed()) {
		game.setState(make_unique<MainMenu>());
	}
}

void Results::draw(const bool bottom) {
	if (!bottom) {
		parent->draw(bottom);
		C2D_DrawRectSolid(0, 0, 1, SCREEN_WIDTH, SCREEN_HEIGHT, RESULTS);

		deadText.draw();
	} else {
		C2D_TargetClear(game.getBottom(), BACKGROUND);

		gui.draw();
	}
}
