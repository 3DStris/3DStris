#include <3dstris/gui/panel.hpp>
#include <3dstris/gui/u32inputfield.hpp>
#include <3dstris/states/configscreen.hpp>
#include <3dstris/states/mainmenu.hpp>
#include <3dstris/util.hpp>
#include <3dstris/version.hpp>

ConfigScreen::ConfigScreen()
	: State(),
	  titleText(game.translate("settings.title")),
	  tipText(game.translate("settings.tip")),

	  dasText(game.translate("settings.das"), Pos{15, 50 - 35},
			  Vector2{0.5f, 0.5f}),
	  arrText(game.translate("settings.arr"), Pos{15, 100 - 35},
			  Vector2{0.5f, 0.5f}),
	  dropTimerText(game.translate("settings.droptimer"), Pos{15, 150 - 35},
					Vector2{0.5f, 0.5f}),

	  saveButton(gui.add<Button>(Pos{10, BSCREEN_HEIGHT - 55}, WH{100, 50},
								 game.translate("save"))),
	  cancelButton(
		  gui.add<Button>(Pos{BSCREEN_WIDTH - 110, BSCREEN_HEIGHT - 55},
						  WH{100, 50}, game.translate("cancel"))),

	  panel(gui.add<Panel>(Pos{10, 10},
						   WH{BSCREEN_WIDTH - 20, BSCREEN_HEIGHT - 80})),
	  tipPanel(gui, {0, SCREEN_HEIGHT - 25}, {SCREEN_WIDTH, 25}, false),

	  dasInputField(gui.add<U32InputField>(Pos{15, 35},
										   WH{BSCREEN_WIDTH - 30, 25}, "ms")),
	  arrInputField(gui.add<U32InputField>(Pos{15, 85},
										   WH{BSCREEN_WIDTH - 30, 25}, "ms")),
	  dropTimerInputField(gui.add<U32InputField>(
		  Pos{15, 135}, WH{BSCREEN_WIDTH - 30, 25}, "ms")) {
	titleText.align(Text::Align::SCREEN_CENTER);

	auto textScale =
		std::min((tipPanel.getWH().x - 10) / tipText.getWH().x, 0.5f);

	tipText.setScale({textScale, textScale});
	tipText.align(Text::Align::CENTER, tipPanel.getPos(), tipPanel.getWH());

	dasInputField.setValue(game.getConfig().das);
	arrInputField.setValue(game.getConfig().arr);
	dropTimerInputField.setValue(game.getConfig().dropTimer);
}

void ConfigScreen::update(const double dt) {
	gui.update(dt);

	if (saveButton.pressed()) {
		auto& config = this->game.getConfig();
		config.das = this->getDas();
		config.arr = this->getArr();
		config.dropTimer = this->getDropTimer();
		config.save();

		this->game.popState();
		return;
	}

	if (cancelButton.pressed() || hidKeysUp() & KEY_B) {
		this->game.popState();
		return;
	}
}

u32 ConfigScreen::getDas() const {
	return dasInputField.getValue();
}

u32 ConfigScreen::getArr() const {
	return arrInputField.getValue();
}

u32 ConfigScreen::getDropTimer() const {
	return dropTimerInputField.getValue();
}

void ConfigScreen::draw(const bool bottom) {
	if (!bottom) {
		C2D_TargetClear(this->game.getTop(), BACKGROUND);

		titleText.draw();

		tipPanel.draw();
		tipText.draw();
	} else {
		C2D_TargetClear(this->game.getBottom(), BACKGROUND);

		gui.draw();

		dasText.draw();
		arrText.draw();
		dropTimerText.draw();
	}
}
