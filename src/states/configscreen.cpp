#include <3dstris/states/configscreen.hpp>
#include <3dstris/states/mainmenu.hpp>
#include <3dstris/util.hpp>
#include <3dstris/version.hpp>

ConfigScreen::ConfigScreen()
	: State(),
	  dasText("DAS"),
	  arrText("ARR"),
	  dasSlider(gui.addFloatInputField(15, 45, BSCREEN_WIDTH - 30, 25)),
	  arrSlider(gui.addFloatInputField(15, 95, BSCREEN_WIDTH - 30, 25)) {
	colBackground = C2D_Color32(34, 34, 34, 255);

	dasText.setPos({15, 50 - 35});
	dasText.setScale({0.5f, 0.5f});

	arrText.setPos({15, 100 - 35});
	arrText.setScale({0.5f, 0.5f});

	dasSlider->setValue(game.getConfig().das);
	arrSlider->setValue(game.getConfig().arr);

	saveButton = gui.addButton(ButtonFlags::NONE, 10, BSCREEN_HEIGHT - 55, 100,
							   50, "Save");

	cancelButton = gui.addButton(ButtonFlags::NONE, BSCREEN_WIDTH - 110,
								 BSCREEN_HEIGHT - 55, 100, 50, "Cancel");
}

void ConfigScreen::update(double dt) {
	gui.update(dt);

	if (saveButton->pressed()) {
		auto& config = this->game.getConfig();
		config.das = this->getDas() / 1000;
		config.arr = this->getArr() / 1000;
		config.saveConfig();

		this->game.popState();
		return;
	}

	if (cancelButton->pressed()) {
		this->game.popState();
		return;
	}
}

float ConfigScreen::getDas() const {
	return dasSlider->getValue();
}

float ConfigScreen::getArr() const {
	return arrSlider->getValue();
}

void ConfigScreen::draw(bool bottom) {
	if (!bottom) {
		C2D_TargetClear(this->game.getTop(), colBackground);
	} else {
		C2D_TargetClear(this->game.getBottom(), colBackground);

		gui.draw();

		dasText.draw();
		arrText.draw();
	}
}
