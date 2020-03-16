#include <3dstris/states/game/sprint.hpp>
#include <3dstris/states/menu/sprintselect.hpp>

SprintSelect::SprintSelect()
	: State(),
	  title(game.translate("sprintselect.title")),

	  twenty(gui.add<Button>(Pos(gui.getWidth() / 4 - 50, 40), WH{100, 50},
							 game.translate("sprintselect.twenty"))),
	  forty(gui.add<Button>(Pos(3 * gui.getWidth() / 4 - 50, 40), WH{100, 50},
							game.translate("sprintselect.forty"))),
	  custom(gui.add<Button>(Pos{0, 40 + 50 + 20}, WH{100, 50},
							 game.translate("sprintselect.custom"),
							 Button::Flags::HCENTER)),

	  back(gui.add<Button>(Pos(0, gui.getHeight() - 50), WH{100, 40},
						   game.translate("back"), Button::Flags::HCENTER)) {
	title.align(Text::Align::SCREEN_CENTER);
}
void SprintSelect::update(const double dt) {
	gui.update(dt);

	if (twenty.pressed()) {
		game.setState(make_unique<Sprint>(20));
	} else if (forty.pressed()) {
		game.setState(make_unique<Sprint>(40));
	} else if (custom.pressed()) {
		constexpr auto DIGITS = std::numeric_limits<u16>::digits10;

		SwkbdState swkbd;
		swkbdInit(&swkbd, SWKBD_TYPE_NUMPAD, 1, DIGITS);
		swkbdSetValidation(&swkbd, SWKBD_NOTEMPTY_NOTBLANK, 0, 0);
		swkbdSetFeatures(&swkbd, SWKBD_FIXED_WIDTH);

		char buf[DIGITS + 1];
		swkbdInputText(&swkbd, buf, DIGITS + 1);

		char* end;
		errno = 0;
		const u16 value = strtoul(buf, &end, 10);
		assert(value < std::numeric_limits<u16>::max());
		if (value != 0 && end[0] == '\0' && errno == 0) {
			game.setState(make_unique<Sprint>(value));
		}
	} else if (back.pressed() || hidKeysDown() & KEY_B) {
		game.popState();
	}
}

void SprintSelect::draw(const bool bottom) {
	if (!bottom) {
		C2D_TargetClear(game.getTop(), gui.getTheme().background);

		title.draw();
	} else {
		C2D_TargetClear(game.getBottom(), gui.getTheme().background);

		gui.draw();
	}
}
