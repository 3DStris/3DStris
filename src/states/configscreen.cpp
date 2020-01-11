#include <3dstris/states/configscreen.hpp>
#include <3dstris/states/mainmenu.hpp>
#include <3dstris/util.hpp>
#include <3dstris/version.hpp>

ConfigScreen::ConfigScreen()
	: State(),
	  tipText(
		  "Use the bottom screen to change settings. Press \uE001 to cancel."),
	  dasText("DAS"),
	  arrText("ARR"),

	  saveButton(
		  gui.add<Button>(Pos{10, BSCREEN_HEIGHT - 55}, WH{100, 50}, "Save")),
	  cancelButton(
		  gui.add<Button>(Pos{BSCREEN_WIDTH - 110, BSCREEN_HEIGHT - 55},
						  WH{100, 50}, "Cancel")),

	  panel(gui.add<Panel>(Pos{10, 10},
						   WH{BSCREEN_WIDTH - 20, BSCREEN_HEIGHT - 130})),
	  tipPanel(gui, {0, SCREEN_HEIGHT - 25}, {SCREEN_WIDTH, 25}, false),

	  dasInputField(gui.add<DoubleInputField>(
		  Pos{15, 35}, WH{BSCREEN_WIDTH - 30, 25}, "ms")),
	  arrInputField(gui.add<DoubleInputField>(
		  Pos{15, 85}, WH{BSCREEN_WIDTH - 30, 25}, "ms")) {
	tipText.setScale({0.5f, 0.5f});
	tipText.align(Text::Align::CENTER, tipPanel.getPos(), tipPanel.getWH());

	dasText.setPos({15, 50 - 35});
	dasText.setScale({0.5f, 0.5f});

	arrText.setPos({15, 100 - 35});
	arrText.setScale({0.5f, 0.5f});

	dasInputField.setValue(game.getConfig().das * 1000);
	arrInputField.setValue(game.getConfig().arr * 1000);
}

void ConfigScreen::update(const double dt) {
	gui.update(dt);

	if (saveButton.pressed()) {
		auto& config = this->game.getConfig();
		config.das = this->getDas() / 1000;
		config.arr = this->getArr() / 1000;
		config.saveConfig();

		this->game.popState();
		return;
	}

	if (cancelButton.pressed() || hidKeysUp() & KEY_B) {
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

void ConfigScreen::draw(const bool bottom) {
	if (!bottom) {
		C2D_TargetClear(this->game.getTop(), BACKGROUND);

		tipPanel.draw();
		tipText.draw();
	} else {
		C2D_TargetClear(this->game.getBottom(), BACKGROUND);

		gui.draw();

		dasText.draw();
		arrText.draw();
	}
}
