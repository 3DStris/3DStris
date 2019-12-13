#include <3dstris/states/configscreen.hpp>
#include <3dstris/util.hpp>
#include <3dstris/version.hpp>

ConfigScreen::ConfigScreen()
	: State(),
	  gui(BSCREEN_WIDTH, BSCREEN_HEIGHT, C2D_Color32(100, 100, 100, 255), WHITE,
		  C2D_Color32(50, 50, 50, 255)),
	  dasText("", WHITE),
	  arrText("", WHITE),
	  dasSlider(gui.addSlider(15, 50, BSCREEN_WIDTH - 30, 5, 20)),
      arrSlider(gui.addSlider(15, 100, BSCREEN_WIDTH - 30, 5, 20)) {
	colBackground = C2D_Color32(34, 34, 34, 255);

	dasText.setPos({15, 10});
	dasText.setScale({0.5f, 0.5f});
	
	arrText.setPos({15, 60});
	arrText.setScale({0.5f, 0.5f});

	dasSlider.setValue(game.getConfig().das / 0.5f);
	arrSlider.setValue(game.getConfig().arr / 0.1f);
}

void ConfigScreen::update(double dt) {
	gui.update(dt);
}

float ConfigScreen::getDas() const {
	// have the slider only go from 0ms to 500ms
	return dasSlider.getValue() * 0.5f;
}

float ConfigScreen::getArr() const {
	// have the slider only go from 0ms to 100ms
	return arrSlider.getValue() * 0.1f;
}

void ConfigScreen::draw(bool bottom) {
	if (!bottom) {
		C2D_TargetClear(this->game.getTop(), colBackground);
	} else {
		C2D_TargetClear(this->game.getBottom(), colBackground);
		
		gui.draw();

		char dasString[100];
		sprintf(dasString, "DAS: %dms", int(getDas()*1000.0f));
		dasText.setText(dasString);

		dasText.draw();

		char arrString[100];
		sprintf(arrString, "ARR: %dms", int(getArr()*1000.0f));
		arrText.setText(arrString);

		arrText.draw();
	}
}
