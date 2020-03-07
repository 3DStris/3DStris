#include <3dstris/states/menu/loadfailed.hpp>

LoadFailed::LoadFailed(const FailType type)
	: State(),
	  failedText(game.translate(FAILTYPE_TO_KEY[static_cast<size_t>(type)])),
	  okButton(gui.add<Button>(Pos{},
							   WH{SCREEN_WIDTH - 100, SCREEN_HEIGHT - 100},
							   game.translate("ok"), Button::Flags::CENTER)) {
	failedText.scale(SCREEN_WIDTH - 10, 0.6f);
	failedText.align(Text::Align::SCREEN_CENTER);
}

void LoadFailed::update(const double dt) {
	gui.update(dt);

	if (okButton.pressed()) {
		game.popState();
	}
}

void LoadFailed::draw(const bool bottom) {
	if (!bottom) {
		C2D_TargetClear(game.getTop(), gui.getTheme().background);

		failedText.draw();
	} else {
		C2D_TargetClear(game.getBottom(), gui.getTheme().background);

		gui.draw();
	}
}

const char* LoadFailed::FAILTYPE_TO_KEY[] = {
	"loadfailed.config", "loadfailed.games", "loadfailed.keybinds"};
