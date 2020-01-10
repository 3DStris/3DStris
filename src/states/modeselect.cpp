#include <3dstris/sprites.h>

#include <3dstris/states/mainmenu.hpp>
#include <3dstris/states/modeselect.hpp>
#include <3dstris/states/sprint.hpp>
#include <3dstris/util.hpp>
#include <3dstris/version.hpp>

ModeSelect::ModeSelect()
	: State(),
	  topText("Select mode"),
	  normalButton(gui.addButton(ButtonFlags::VCENTER, BSCREEN_WIDTH / 4.0 - 50,
								 -1, 100, 50, "Normal")),
	  sprintButton(gui.addButton(ButtonFlags::VCENTER,
								 3 * BSCREEN_WIDTH / 4.0 - 50, -1, 100, 50,
								 "Sprint")),
	  backButton(gui.addButton(ButtonFlags::HCENTER, -1, BSCREEN_HEIGHT - 50,
							   100, 40, "Back")) {
	topText.setPos({(SCREEN_WIDTH - topText.getWH().x) / 2.0f,
					(SCREEN_HEIGHT - topText.getWH().y) / 2.0f});
}
void ModeSelect::update(double dt) {
	gui.update(dt);

	if (normalButton.pressed()) {
		this->game.setState(make_unique<Playing>(), false, true);
		return;
	}

	if (sprintButton.pressed()) {
		this->game.setState(make_unique<Sprint>(), false, false);
		return;
	}

	if (backButton.pressed()) {
		this->game.popState();
		return;
	}
}

void ModeSelect::draw(bool bottom) {
	if (!bottom) {
		C2D_TargetClear(this->game.getTop(), BACKGROUND);

		topText.draw();
	} else {
		C2D_TargetClear(this->game.getBottom(), BACKGROUND);

		gui.draw();
	}
}
