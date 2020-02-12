#include <3dstris/gui/panel.hpp>
#include <3dstris/gui/u32inputfield.hpp>
#include <3dstris/states/configscreen.hpp>
#include <3dstris/states/mainmenu.hpp>
#include <3dstris/util.hpp>
#include <3dstris/version.hpp>

ConfigScreen::ConfigScreen()
	: State(),
	  title(game.translate("settings.title")),
	  tipText(game.translate("settings.tip")),

	  dasLabel(game.translate("settings.das"), Pos{15, 50 - 35},
			   Vector2{0.5f, 0.5f}),
	  arrLabel(game.translate("settings.arr"), Pos{15, 100 - 35},
			   Vector2{0.5f, 0.5f}),
	  dropTimerLabel(game.translate("settings.droptimer"), Pos{15, 150 - 35},
					 Vector2{0.5f, 0.5f}),

	  save(gui.add<Button>(Pos{10, BSCREEN_HEIGHT - 55}, WH{100, 50},
						   game.translate("save"))),
	  cancel(gui.add<Button>(Pos{BSCREEN_WIDTH - 110, BSCREEN_HEIGHT - 55},
							 WH{100, 50}, game.translate("cancel"))),

	  panel(gui.add<Panel>(Pos{10, 10},
						   WH{BSCREEN_WIDTH - 20, BSCREEN_HEIGHT - 80})),
	  tip(gui, {0, SCREEN_HEIGHT - 25}, {SCREEN_WIDTH, 25}, false),

	  das(gui.add<U32InputField>(Pos{15, 35}, WH{BSCREEN_WIDTH - 50 - 115, 25},
								 "ms")),
	  arr(gui.add<U32InputField>(Pos{15, 85}, WH{BSCREEN_WIDTH - 30, 25},
								 "ms")),
	  dropTimer(gui.add<U32InputField>(Pos{15, 135}, WH{BSCREEN_WIDTH - 30, 25},
									   "ms")),
	  useTextures(gui.add<ToggleButton>(Pos{BSCREEN_WIDTH - 20 - 115, 35},
										WH{115, 30},
										game.translate("settings.usetextures"),
										game.getConfig().useTextures)) {
	title.align(Text::Align::SCREEN_CENTER);

	const auto tipTextScale =
		std::min((tip.getWH().x - 10) / tipText.getWH().x, 0.5f);
	tipText.setScale({tipTextScale, tipTextScale});
	tipText.align(Text::Align::CENTER, tip.getPos(), tip.getWH());

	das.setValue(game.getConfig().das);
	arr.setValue(game.getConfig().arr);
	dropTimer.setValue(game.getConfig().dropTimer);
}

void ConfigScreen::update(const double dt) {
	gui.update(dt);

	if (save.pressed()) {
		auto& config = this->game.getConfig();
		config.das = das.getValue();
		config.arr = arr.getValue();
		config.dropTimer = dropTimer.getValue();
		config.useTextures = useTextures.getValue();
		config.save();

		this->game.popState();
		return;
	}

	if (cancel.pressed() || hidKeysUp() & KEY_B) {
		this->game.popState();
		return;
	}
}

void ConfigScreen::draw(const bool bottom) {
	if (!bottom) {
		C2D_TargetClear(this->game.getTop(), BACKGROUND);

		title.draw();

		tip.draw();
		tipText.draw();
	} else {
		C2D_TargetClear(this->game.getBottom(), BACKGROUND);

		gui.draw();

		dasLabel.draw();
		arrLabel.draw();
		dropTimerLabel.draw();
	}
}
