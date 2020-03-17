#include <3dstris/gui/widgets/special/keybindbutton.hpp>
#include <3dstris/states/menu/settings/gameplay.hpp>
#include <3dstris/states/menu/settings/gameplay/keybindselect.hpp>
#include <3dstris/states/menu/settings/visual.hpp>

GameplaySettings::GameplaySettings() noexcept
	: BaseSettings("settings.gameplay.title"),

	  dasLabel(game.translate("settings.gameplay.das"), Pos{15, 50 - 35},
			   {0.5f, 0.5f}),
	  arrLabel(game.translate("settings.gameplay.arr"), Pos{15, 100 - 35},
			   {0.5f, 0.5f}),
	  dropTimerLabel(game.translate("settings.gameplay.droptimer"),
					 Pos{15, 150 - 35}, {0.5f, 0.5f}),

	  nextTip(gui, Pos(SCREEN_WIDTH - 100, SCREEN_HEIGHT - 25 - 25),
			  WH{100, 25}),
	  nextTipText(
		  sdscatfmt(sdsempty(), "%s %S", KeybindButton::KEY_TO_GLYPH.at(KEY_R),
					game.translate("settings.visual.title")),
		  Pos(SCREEN_WIDTH - 100 + 5, 0)),

	  das(gui.add<IntegerInputField<u16>>(
		  Pos{15, 35}, WH(gui.getWidth() - 50 - 115, 25), "ms")),
	  arr(gui.add<IntegerInputField<u16>>(Pos{15, 85},
										  WH(gui.getWidth() - 30, 25), "ms")),
	  dropTimer(gui.add<IntegerInputField<u16>>(
		  Pos{15, 135}, WH(gui.getWidth() - 30, 25), "ms")),
	  keybinds(gui.add<Button>(Pos(gui.getWidth() - 20 - 115, 35), WH{115, 30},
							   game.translate("settings.gameplay.keybinds"))) {
	nextTipText.scale(nextTip.getWH().x, 0.65f);
	nextTipText.align(Text::Align::VCENTER, nextTip.getPos(), nextTip.getWH());

	das.setValue(game.getConfig().das);
	arr.setValue(game.getConfig().arr);
	dropTimer.setValue(game.getConfig().dropTimer);
}

void GameplaySettings::update(const double dt) noexcept {
	config.das = das.getValue();
	config.arr = arr.getValue();
	config.dropTimer = dropTimer.getValue();

	if (keybinds.pressed()) {
		game.pushState(make_unique<KeybindSelect>());
	} else if (hidKeysDown() & KEY_R) {
		game.pushState(make_unique<VisualSettings>());
	}

	BaseSettings::update(dt);
}

void GameplaySettings::draw(const bool bottom) noexcept {
	BaseSettings::draw(bottom);

	if (!bottom) {
		nextTip.draw();
		nextTipText.draw();
	} else {
		dasLabel.draw();
		arrLabel.draw();
		dropTimerLabel.draw();
	}
}
