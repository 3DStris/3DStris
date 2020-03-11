#include <3dstris/states/game/playing.hpp>
#include <3dstris/states/menu/modeselect.hpp>
#include <3dstris/states/menu/sprintselect.hpp>

ModeSelect::ModeSelect()
	: State(),
	  title(game.translate("modeselect.title")),

	  normalButton(gui.add<Button>(Pos(gui.getWidth() / 4 - 50, 0), WH{100, 50},
								   game.translate("modeselect.normal"),
								   Button::Flags::VCENTER)),
	  sprintButton(gui.add<Button>(
		  Pos(3 * gui.getWidth() / 4 - 50, 0), WH{100, 50},
		  game.translate("modeselect.sprint"), Button::Flags::VCENTER)),
	  backButton(gui.add<Button>(Pos(0, gui.getHeight() - 50), WH{100, 40},
								 game.translate("back"),
								 Button::Flags::HCENTER)) {
	title.align(Text::Align::SCREEN_CENTER);
}
void ModeSelect::update(const double dt) {
	gui.update(dt);

	if (normalButton.pressed()) {
		game.setState(make_unique<Playing>());
	} else if (sprintButton.pressed()) {
		game.pushState(make_unique<SprintSelect>());
	} else if (backButton.pressed() || hidKeysDown() & KEY_B) {
		game.popState();
	}
}

void ModeSelect::draw(const bool bottom) {
	if (!bottom) {
		C2D_TargetClear(game.getTop(), gui.getTheme().background);

		title.draw();
	} else {
		C2D_TargetClear(game.getBottom(), gui.getTheme().background);

		gui.draw();
	}
}
