#include <3dstris/sprites.h>
#include <3dstris/states/loadfailed.hpp>
#include <3dstris/states/mainmenu.hpp>
#include <3dstris/util.hpp>
#include <3dstris/version.hpp>

LoadFailed::LoadFailed(const FailType type)
	: State(),
	  failedText(
		  type == FailType::CONFIG
			  ? "Failed to load config; your settings have been reset."
			  : "Failed to load games; your saved games have been reset."),

	  okButton(gui.add<Button>(Pos{-1, -1},
							   WH{SCREEN_WIDTH - 100, SCREEN_HEIGHT - 100},
							   "OK", Button::Flags::CENTER)) {
	auto textScale = std::min((SCREEN_WIDTH - 10) / failedText.getWH().x, 0.6f);
	failedText.setScale({textScale, textScale});
	failedText.align(Text::Align::SCREEN_CENTER);
}

void LoadFailed::update(const double dt) {
	gui.update(dt);

	if (okButton.pressed()) {
		this->game.popState();
	}
}

void LoadFailed::draw(const bool bottom) {
	if (!bottom) {
		C2D_TargetClear(this->game.getTop(), BACKGROUND);

		failedText.draw();
	} else {
		C2D_TargetClear(this->game.getBottom(), BACKGROUND);

		gui.draw();
	}
}
