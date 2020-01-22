#include <3dstris/sprites.h>

#include <3dstris/states/mainmenu.hpp>
#include <3dstris/states/modeselect.hpp>
#include <3dstris/states/sprint.hpp>
#include <3dstris/util.hpp>
#include <3dstris/version.hpp>

ModeSelect::ModeSelect()
	: State(),
	  topText("Select a mode"),

	  normalButton(gui.add<Button>(Pos{BSCREEN_WIDTH / 4.0 - 50, -1},
								   WH{100, 50}, "Normal",
								   Button::Flags::VCENTER)),
	  sprintButton(gui.add<Button>(Pos{3 * BSCREEN_WIDTH / 4.0 - 50, -1},
								   WH{100, 50}, "Sprint",
								   Button::Flags::VCENTER)),
	  backButton(gui.add<Button>(Pos{-1, BSCREEN_HEIGHT - 50}, WH{100, 40},
								 "Back", Button::Flags::HCENTER)) {
	topText.align(Text::Align::SCREEN_CENTER);
}
void ModeSelect::update(const double dt) {
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

void ModeSelect::draw(const bool bottom) {
	if (!bottom) {
		C2D_TargetClear(this->game.getTop(), BACKGROUND);

		topText.draw();
	} else {
		C2D_TargetClear(this->game.getBottom(), BACKGROUND);

		gui.draw();
	}
}
