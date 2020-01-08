#include <3dstris/states/mainmenu.hpp>
#include <3dstris/states/results.hpp>
#include <algorithm>

Results::Results(State* parent)
	: State(),
	  deadText("Game over"),
	  parent(parent),
	  restartButton(
		  gui.addButton(ButtonFlags::HCENTER, -1, BSCREEN_HEIGHT / 3.0f - 10, 150, 60, "Restart")),
	  menuButton(
		  gui.addButton(ButtonFlags::HCENTER, -1, BSCREEN_HEIGHT - 45 - 10, 100, 45, "Menu")) {
	colBackground = C2D_Color32(34, 34, 34, 255);

	deadText.setScale({2, 2});
	deadText.setPos({(SCREEN_WIDTH - deadText.getWH().x) / 2,
					   (SCREEN_HEIGHT - deadText.getWH().y) / 2});
}

void Results::update(double dt) {
	gui.update(dt);

	if (restartButton.pressed()) {
		this->game.setState(make_unique<Playing>(), false, true);
		return;
	}

	if (menuButton.pressed()) {
		this->game.setState(make_unique<MainMenu>());
	}
}

void Results::draw(bool bottom) {
	if (!bottom) {
		parent->draw(bottom);
		C2D_DrawRectSolid(0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, PAUSED);

		deadText.draw();
	} else {
		C2D_TargetClear(this->game.getBottom(), colBackground);

		gui.draw();
	}
}
