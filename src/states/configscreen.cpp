#include <3dstris/states/configscreen.hpp>
#include <3dstris/util.hpp>
#include <3dstris/version.hpp>

ConfigScreen::ConfigScreen()
	: State(),
	  gui(BSCREEN_WIDTH, BSCREEN_HEIGHT, C2D_Color32(100, 100, 100, 255), WHITE,
		  C2D_Color32(50, 50, 50, 255)) {
	colBackground = C2D_Color32(34, 34, 34, 255);

	slider = gui.addSlider(50, 50, 100);

	dynamicTextBuf = C2D_TextBufNew(256);
}

void ConfigScreen::update(double dt) {
	gui.update(dt);
}

void ConfigScreen::draw(bool bottom) {
	if (!bottom) {
		C2D_TargetClear(this->game.getTop(), colBackground);
	} else {
		C2D_TextBufClear(dynamicTextBuf);
		C2D_TargetClear(this->game.getBottom(), colBackground);
		
		gui.draw();
		
		C2D_Text valueText;

		char valueString[10];
		sprintf(valueString, "%.3f", slider->getValue());
		C2D_TextParse(&valueText, dynamicTextBuf, valueString);
		C2D_TextOptimize(&valueText);

		C2D_DrawText(&valueText, C2D_WithColor, 1, 1, 0, 0.5f, 0.5f, WHITE);
	}
}
