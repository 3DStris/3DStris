#include <3dstris/states/menu/mainmenu.hpp>
#include <3dstris/states/menu/settings/base.hpp>

BaseConfig BaseSettings::config = Game::get().getConfig();

BaseSettings::BaseSettings(const StringView titleKey) noexcept
	: title(game.translate(titleKey)),

	  tip(gui, Pos{0, SCREEN_HEIGHT - 25}, WH(SCREEN_WIDTH, 25), false),
	  tipText(game.translate("settings.tip")),

	  panel(gui.add<Panel>(Pos{10, 10},
						   WH(gui.getWidth() - 20, gui.getHeight() - 80))),

	  save(gui.add<Button>(Pos(10, gui.getHeight() - 50), WH{75, 40},
						   game.translate("save"))),
	  cancel(gui.add<Button>(Pos(gui.getWidth() - 90, gui.getHeight() - 50),
							 WH{80, 40}, game.translate("cancel"))) {
	title.align(Text::Align::SCREEN_CENTER);

	tipText.scale(tip.getWH().x, 0.5f);
	tipText.align(Text::Align::CENTER, tip.getPos(), tip.getWH());
}

void BaseSettings::update(const double dt) {
	gui.update(dt);

	if (cancel.pressed() || hidKeysUp() & KEY_B) {
		config = game.getConfig();
		game.setState(make_unique<MainMenu>());
		return;
	}

	if (save.pressed()) {
		game.getConfig() = config;
		game.getConfig().save();

		game.setState(make_unique<MainMenu>());
		return;
	}
}

void BaseSettings::draw(const bool bottom) const {
	if (!bottom) {
		C2D_TargetClear(game.getTop(), gui.getTheme().background);

		title.draw();

		tip.draw();
		tipText.draw();
	} else {
		C2D_TargetClear(game.getBottom(), gui.getTheme().background);

		gui.draw();
	}
}
