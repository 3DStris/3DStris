#include <3dstris/states/modeselect.hpp>
#include <3dstris/states/playing.hpp>
#include <3dstris/states/sprint.hpp>

ModeSelect::ModeSelect()
	: State(),
	  topText(game.translate("modeselect.title")),

	  normalButton(gui.add<Button>(
		  Pos{BSCREEN_WIDTH / 4.0 - 50, -1}, WH{100, 50},
		  game.translate("modeselect.normal"), Button::Flags::VCENTER)),
	  sprintButton(gui.add<Button>(
		  Pos{3 * BSCREEN_WIDTH / 4.0 - 50, -1}, WH{100, 50},
		  game.translate("modeselect.sprint"), Button::Flags::VCENTER)),
	  backButton(gui.add<Button>(Pos{-1, BSCREEN_HEIGHT - 50}, WH{100, 40},
								 game.translate("back"),
								 Button::Flags::HCENTER)) {
	topText.align(Text::Align::SCREEN_CENTER);
}
void ModeSelect::update(const double dt) {
	gui.update(dt);

	if (normalButton.pressed()) {
		game.setState(make_unique<Playing>(), false, true);
		return;
	}

	if (sprintButton.pressed()) {
		game.setState(make_unique<Sprint>(), false, false);
		return;
	}

	if (backButton.pressed()) {
		game.popState();
		return;
	}
}

void ModeSelect::draw(const bool bottom) {
	if (!bottom) {
		C2D_TargetClear(game.getTop(), BACKGROUND);

		topText.draw();
	} else {
		C2D_TargetClear(game.getBottom(), BACKGROUND);

		gui.draw();
	}
}
