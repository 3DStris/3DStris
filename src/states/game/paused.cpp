#include <3dstris/states/game/paused.hpp>
#include <3dstris/states/menu/mainmenu.hpp>

Paused::Paused(Ingame* parent)
	: State(),
	  parent(parent),

	  title(game.translate("paused.title")),

	  restart(gui.add<Button>(Pos{0, 6}, WH{100, 45},
							  game.translate("results.restart"),
							  Button::Flags::HCENTER)),
	  unpause(gui.add<Button>(Pos{0, 10}, WH{200, 115},
							  game.translate("paused.resume"),
							  Button::Flags::CENTER)),
	  menu(gui.add<Button>(Pos{0, BSCREEN_HEIGHT - 40 - 10}, WH{100, 45},
						   game.translate("menu"), Button::Flags::HCENTER)) {
	title.setScale({2, 2});
	title.align(Text::Align::SCREEN_CENTER);
}

void Paused::update(const double dt) {
	gui.update(dt);

	if (restart.pressed()) {
		assert(parent != nullptr);

		parent->reset();
		game.popState();
		return;
	}

	const u32 kDown = hidKeysDown();
	if (unpause.pressed() || (kDown > KEY_A && kDown <= KEY_ZR)) {
		game.popState();
	} else if (menu.pressed()) {
		game.setState(make_unique<MainMenu>());
	}
}

void Paused::draw(const bool bottom) const {
	if (!bottom) {
		assert(parent != nullptr);

		parent->draw(bottom);
		C2D_DrawRectSolid(0, 0, 1, SCREEN_WIDTH, SCREEN_HEIGHT, PAUSED);

		title.draw();
	} else {
		C2D_TargetClear(game.getBottom(), gui.getTheme().background);

		gui.draw();
	}
}
