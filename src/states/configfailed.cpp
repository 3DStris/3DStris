#include <3dstris/sprites.h>
#include <3dstris/states/configfailed.hpp>
#include <3dstris/util.hpp>
#include <3dstris/version.hpp>

ConfigFailed::ConfigFailed()
	: State(),
	  gui(BSCREEN_WIDTH, BSCREEN_HEIGHT, C2D_Color32(100, 100, 100, 255), WHITE,
		  C2D_Color32(50, 50, 50, 255)) {
	colBackground = C2D_Color32(34, 34, 34, 255);

	const char* failedString =
		"Failed to load config; your settings have been reset.";

	C2D_TextParse(&failedText, C2D_TextBufNew(strlen(failedString)),
				  failedString);
	C2D_TextOptimize(&failedText);

	gui.addButton(ButtonFlags::CENTER, -1, -1, SCREEN_WIDTH - 100,
				  SCREEN_HEIGHT - 100, "OK",
				  [this]() { this->game.setState(new MainMenu()); });
}

void ConfigFailed::update(double dt) {
	gui.update(dt);
}

void ConfigFailed::draw(bool bottom) {
	if (!bottom) {
		C2D_TargetClear(this->game.getTop(), colBackground);

		// Get text height
		float textWidth, textHeight;
		C2D_TextGetDimensions(&failedText, 0.5f, 0.5f, &textWidth, &textHeight);

		// Draw version text
		C2D_DrawText(&failedText, C2D_WithColor,
					 SCREEN_WIDTH / 2 - textWidth / 2,
					 SCREEN_HEIGHT / 2 - textHeight / 2, 0, 0.5f, 0.5f, WHITE);
	} else {
		C2D_TargetClear(this->game.getBottom(), colBackground);

		gui.draw();
	}
}
