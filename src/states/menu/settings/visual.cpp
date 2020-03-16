#include <3dstris/gui/widgets/special/keybindbutton.hpp>
#include <3dstris/states/menu/settings/visual.hpp>

VisualSettings::VisualSettings()
	: BaseSettings("settings.visual.title"),

	  backTip(gui, Pos{0, SCREEN_HEIGHT - 25 - 25}, WH{100, 25}),
	  backTipText(
		  sdscatfmt(sdsempty(), "%s %S", KeybindButton::KEY_TO_GLYPH.at(KEY_L),
					game.translate("settings.gameplay.title")),
		  Pos{6, 0}),

	  useTextures(gui.add<ToggleButton>(
		  Pos(10 + (gui.getWidth() - 20 - 115) / 2,
			  10 + (gui.getHeight() - 80 - 30) / 2),
		  WH{115, 30}, game.translate("settings.visual.usetextures"),
		  config.useTextures)) {
	backTipText.scale(backTip.getWH().x, 0.65f);
	backTipText.align(Text::Align::VCENTER, backTip.getPos(), backTip.getWH());
}

void VisualSettings::update(const double dt) {
	config.useTextures = useTextures.getValue();

	if (hidKeysDown() & KEY_L) {
		game.popState();
		return;
	}

	BaseSettings::update(dt);
}

void VisualSettings::draw(const bool bottom) {
	BaseSettings::draw(bottom);

	if (!bottom) {
		backTip.draw();
		backTipText.draw();
	}
}
