#include <3dstris/sprites.h>
#include <3dstris/states/configfailed.hpp>
#include <3dstris/states/mainmenu.hpp>
#include <3dstris/util.hpp>
#include <3dstris/version.hpp>

ConfigFailed::ConfigFailed()
	: State(),
	  failedText("Failed to load config; your settings have been reset."),
	  okButton(gui.add<Button>(-1, -1, SCREEN_WIDTH - 100, SCREEN_HEIGHT - 100,
							   "OK", Button::Flags::CENTER)) {
	failedText.setScale({0.6f, 0.6f});
	failedText.align(Text::Align::SCREEN_CENTER);
}

void ConfigFailed::update(double dt) {
	gui.update(dt);

	if (okButton.pressed()) {
		this->game.setState(make_unique<MainMenu>());
	}
}

void ConfigFailed::draw(bool bottom) {
	if (!bottom) {
		C2D_TargetClear(this->game.getTop(), BACKGROUND);

		failedText.draw();
	} else {
		C2D_TargetClear(this->game.getBottom(), BACKGROUND);

		gui.draw();
	}
}
