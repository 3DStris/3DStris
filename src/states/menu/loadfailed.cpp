#include <3dstris/states/menu/loadfailed.hpp>

LoadFailed::LoadFailed(const FailType type) noexcept
	: State(),
	  reason(game.translate(FAILTYPE_TO_KEY[static_cast<size_t>(type)])),
	  ok(gui.add<Button>(Pos{},
						 WH{gui.getWidth() - 100.0f, gui.getWidth() - 100.0f},
						 game.translate("ok"), Button::Flags::CENTER)) {
	reason.scale(gui.getWidth() - 10.0f, 0.6f);
	reason.align(Text::Align::SCREEN_CENTER);
}

void LoadFailed::update(const double dt) noexcept {
	gui.update(dt);

	if (ok.pressed()) {
		game.popState();
	}
}

void LoadFailed::draw(const bool bottom) const noexcept {
	if (!bottom) {
		C2D_TargetClear(game.getTop(), gui.getTheme().background);

		reason.draw();
	} else {
		C2D_TargetClear(game.getBottom(), gui.getTheme().background);

		gui.draw();
	}
}

const char* LoadFailed::FAILTYPE_TO_KEY[] = {
	"loadfailed.config", "loadfailed.games", "loadfailed.keybinds"};
