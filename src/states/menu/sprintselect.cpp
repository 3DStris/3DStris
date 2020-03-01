#include <3dstris/states/game/sprint.hpp>
#include <3dstris/states/menu/sprintselect.hpp>

SprintSelect::SprintSelect()
	: State(),
	  title(game.translate("sprintselect.title")),

	  twentyButton(gui.add<Button>(Pos{BSCREEN_WIDTH / 4 - 50, 40}, WH{100, 50},
								   game.translate("sprintselect.twenty"))),
	  fortyButton(gui.add<Button>(Pos{3 * BSCREEN_WIDTH / 4 - 50, 40},
								  WH{100, 50},
								  game.translate("sprintselect.forty"))),
	  customButton(gui.add<Button>(Pos{-1, 40 + 50 + 20}, WH{100, 50},
								   game.translate("sprintselect.custom"),
								   Button::Flags::HCENTER)),

	  backButton(gui.add<Button>(Pos{-1, BSCREEN_HEIGHT - 50}, WH{100, 40},
								 game.translate("back"),
								 Button::Flags::HCENTER)) {
	title.align(Text::Align::SCREEN_CENTER);
}
void SprintSelect::update(const double dt) {
	gui.update(dt);

	if (twentyButton.pressed()) {
		game.setState(make_unique<Sprint>(20), false, true);
		return;
	}

	if (fortyButton.pressed()) {
		game.setState(make_unique<Sprint>(40), false, true);
		return;
	}

	if (customButton.pressed()) {
		constexpr auto DIGITS = std::numeric_limits<u16>::digits10;

		SwkbdState swkbd;
		swkbdInit(&swkbd, SWKBD_TYPE_NUMPAD, 1, DIGITS);
		swkbdSetValidation(&swkbd, SWKBD_NOTEMPTY_NOTBLANK, 0, 0);
		swkbdSetFeatures(&swkbd, SWKBD_FIXED_WIDTH);

		char* buf = new char[DIGITS + 1];
		swkbdInputText(&swkbd, buf, DIGITS + 1);

		char* end;
		errno = 0;
		const u16 value = strtoul(buf, &end, 10);
		assert(value < std::numeric_limits<u16>::max());
		if (value != 0 && end[0] == '\0' && errno == 0) {
			game.setState(make_unique<Sprint>(value), false, true);
		}

		delete[] buf;

		return;
	}

	if (backButton.pressed()) {
		game.popState();
		return;
	}
}

void SprintSelect::draw(const bool bottom) {
	if (!bottom) {
		C2D_TargetClear(game.getTop(), BACKGROUND);

		title.draw();
	} else {
		C2D_TargetClear(game.getBottom(), BACKGROUND);

		gui.draw();
	}
}
