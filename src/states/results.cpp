#include <3dstris/states/mainmenu.hpp>
#include <3dstris/states/results.hpp>
#include <algorithm>

Results::Results(Ingame* parent)
	: State(),
      topText("Game over"),
	  parent(parent),
	  restartButton(
		  gui.addButton(ButtonFlags::HCENTER, -1, BSCREEN_HEIGHT / 3.0f - 10, 150, 60, "Restart")),
	  menuButton(
		  gui.addButton(ButtonFlags::HCENTER, -1, BSCREEN_HEIGHT - 45 - 10, 100, 45, "Menu")) {

    topText.setScale({2, 2});
    topText.setPos({(SCREEN_WIDTH - topText.getWH().x) / 2,
                       (SCREEN_HEIGHT - topText.getWH().y) / 2});
}

Results::Results(Ingame *parent, double sprintTime) : Results(parent) {
    topText.setText(sdscatprintf(sdsempty(), "Good job! You got: %.3fs", sprintTime));
    topText.setScale({1.3, 1.3});
    topText.setPos({(SCREEN_WIDTH - topText.getWH().x) / 2,
                       (SCREEN_HEIGHT - topText.getWH().y) / 2});
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
		C2D_DrawRectSolid(0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, PAUSED);

        topText.draw();
	} else {
        C2D_TargetClear(this->game.getBottom(), BACKGROUND);

		gui.draw();
	}
}
