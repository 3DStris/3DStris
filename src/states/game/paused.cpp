#include <3dstris/states/game/paused.hpp>
#include <3dstris/states/menu/mainmenu.hpp>

Paused::Paused(Ingame* parent)
	: State(),
	  parent(parent),

	  pausedText(game.translate("paused.title")),

	  restartButton(gui.add<Button>(Pos{0, 6}, WH{100, 45},
									game.translate("results.restart"),
									Button::Flags::HCENTER)),
	  unpauseButton(gui.add<Button>(Pos{0, 10}, WH{200, 115},
									game.translate("paused.resume"),
									Button::Flags::CENTER)),
	  menuButton(gui.add<Button>(Pos{0, BSCREEN_HEIGHT - 40 - 10}, WH{100, 45},
								 game.translate("menu"),
								 Button::Flags::HCENTER)) {
	pausedText.setScale({2, 2});
	pausedText.align(Text::Align::SCREEN_CENTER);
}

void Paused::update(const double dt) {
	gui.update(dt);

	if (restartButton.pressed()) {
		assert(parent != nullptr);

		parent->reset();
		game.popState();
		return;
	}

	const u32 kDown = hidKeysDown();
	if (unpauseButton.pressed() || (kDown > KEY_A && kDown <= KEY_ZR)) {
		game.popState();
		return;
	}

	if (menuButton.pressed()) {
		game.setState(make_unique<MainMenu>());
		return;
	}
}

void Paused::draw(const bool bottom) {
	if (!bottom) {
		assert(parent != nullptr);

		parent->draw(bottom);
		C2D_DrawRectSolid(0, 0, 1, SCREEN_WIDTH, SCREEN_HEIGHT, PAUSED);

		pausedText.draw();
	} else {
		C2D_TargetClear(game.getBottom(), BACKGROUND);

		gui.draw();
	}
}
