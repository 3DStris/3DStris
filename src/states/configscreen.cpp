#include <3dstris/states/configscreen.hpp>
#include <3dstris/states/mainmenu.hpp>
#include <3dstris/util.hpp>
#include <3dstris/version.hpp>

ConfigScreen::ConfigScreen()
	: State(),
	  dasText("DAS"),
	  arrText("ARR"),
	  saveButton(gui.addButton(ButtonFlags::NONE, 10, BSCREEN_HEIGHT - 55, 100,
							   50, "Save")),
	  cancelButton(gui.addButton(ButtonFlags::NONE, BSCREEN_WIDTH - 110,
								 BSCREEN_HEIGHT - 55, 100, 50, "Cancel")),
	  dasInputField(
		  gui.addFloatInputField(15, 45, BSCREEN_WIDTH - 30, 25, "ms")),
	  arrInputField(
		  gui.addFloatInputField(15, 95, BSCREEN_WIDTH - 30, 25, "ms")) {
	colBackground = C2D_Color32(34, 34, 34, 255);

	dasText.setPos({15, 50 - 35});
	dasText.setScale({0.5f, 0.5f});

	arrText.setPos({15, 100 - 35});
	arrText.setScale({0.5f, 0.5f});

	dasInputField.setValue(game.getConfig().das * 1000);
	arrInputField.setValue(game.getConfig().arr * 1000);
}

void ConfigScreen::update(double dt) {
	gui.update(dt);

	if (saveButton.pressed()) {
		auto& config = this->game.getConfig();
		config.das = this->getDas() / 1000;
		config.arr = this->getArr() / 1000;
		config.saveConfig();

		this->game.popState();
		return;
	}

	if (cancelButton.pressed()) {
		this->game.popState();
		return;
	}
}

double ConfigScreen::getDas() const {
	return dasInputField.getValue();
}

double ConfigScreen::getArr() const {
	return arrInputField.getValue();
}

void ConfigScreen::draw(bool bottom) {
	if (!bottom) {
		C2D_TargetClear(this->game.getTop(), colBackground);
	} else {
		C2D_TargetClear(this->game.getBottom(), colBackground);

		C2D_DrawRectSolid(10, 10, 0, BSCREEN_WIDTH - 20, BSCREEN_HEIGHT - 130,
						  PANEL);
		GUI::drawOutline(10, 10, BSCREEN_WIDTH - 20, BSCREEN_HEIGHT - 130, 2,
						 PANEL_BORDER);

		gui.draw();

		dasText.draw();
		arrText.draw();
	}
}
