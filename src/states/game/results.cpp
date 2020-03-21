#include <3dstris/states/game/results.hpp>
#include <3dstris/states/menu/mainmenu.hpp>
#include <algorithm>

Results::Results(Ingame* parent)
	: State(),
	  parent(parent),

	  dead(game.translate("results.dead")),

	  restart(gui.add<Button>(Pos{-1, gui.getHeight() / 3.0f - 10}, WH{150, 60},
							  game.translate("results.restart"),
							  Button::Flags::HCENTER)),
	  menu(gui.add<Button>(Pos(-1, gui.getHeight() - 45 - 10), WH{100, 45},
						   game.translate("menu"), Button::Flags::HCENTER)) {
	dead.setScale({2, 2});
	dead.align(Text::Align::SCREEN_CENTER);
}

void Results::update(const double dt) {
	gui.update(dt);

	if (restart.pressed()) {
		parent->reset();
		game.popState(false, true);
	}

	if (menu.pressed() || hidKeysDown() & KEY_B) {
		game.setState(make_unique<MainMenu>());
	}
}

void Results::draw(const bool bottom) const {
	if (!bottom) {
		parent->draw(bottom);
		C2D_DrawRectSolid(0, 0, 1, SCREEN_WIDTH, SCREEN_HEIGHT, RESULTS);

		dead.draw();
	} else {
		C2D_TargetClear(game.getBottom(), gui.getTheme().background);

		gui.draw();
	}
}
