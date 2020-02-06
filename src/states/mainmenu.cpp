#include <3dstris/sprites.h>

#include <3dstris/states/configscreen.hpp>
#include <3dstris/states/languages.hpp>
#include <3dstris/states/mainmenu.hpp>
#include <3dstris/states/modeselect.hpp>
#include <3dstris/states/sprinttimes.hpp>
#include <3dstris/util.hpp>
#include <3dstris/version.hpp>

MainMenu::MainMenu()
	: State(),
	  versionText(
		  sdscatfmt(sdsempty(), "v%s-%s", _3DSTRIS_VERSION, _3DSTRIS_GIT_HASH)),

	  icon(C2D_SpriteSheetGetImage(game.getSpriteSheet(), sprites_icon_idx)),

	  playButton(gui.add<Button>(Pos{-1, 10}, WH{100, 50},
								 game.translate("mainmenu.play"),
								 Button::Flags::HCENTER)),
	  settingsButton(gui.add<Button>(Pos{-1, 100}, WH{100, 50},
									 game.translate("mainmenu.settings"),
									 Button::Flags::HCENTER)),
	  exitButton(gui.add<Button>(Pos{-1, BSCREEN_HEIGHT - 50}, WH{100, 40},
								 game.translate("exit"),
								 Button::Flags::HCENTER)),

	  gamesButton(gui.add<Button>(Pos{10, BSCREEN_HEIGHT - 40 - 10}, WH{75, 40},
								  game.translate("mainmenu.games"))),
	  languagesButton(gui.add<Button>(
		  Pos{BSCREEN_WIDTH - 80 - 10, BSCREEN_HEIGHT - 40 - 10}, WH{75, 40},
		  game.translate("mainmenu.languages"))) {
	versionText.setScale({0.5f, 0.5f});
	versionText.setPos({3, SCREEN_HEIGHT - versionText.getWH().y / 1.25f - 5});
}
void MainMenu::update(const double dt) {
	u32 kDown = hidKeysDown();

	if (kDown & KEY_START) {
		this->game.exit = true;
		return;
	}
	gui.update(dt);

	if (playButton.pressed()) {
		this->game.pushState(make_unique<ModeSelect>());
		return;
	}
	if (settingsButton.pressed()) {
		this->game.pushState(make_unique<ConfigScreen>());
		return;
	}
	if (exitButton.pressed()) {
		this->game.exit = true;
	}

	if (gamesButton.pressed()) {
		this->game.pushState(make_unique<SprintTimes>());
	}
	if (languagesButton.pressed()) {
		this->game.pushState(make_unique<LanguageSelect>());
	}
}

void MainMenu::draw(const bool bottom) {
	if (!bottom) {
		C2D_TargetClear(this->game.getTop(), BACKGROUND);

		// The 48x48 icon sprite was converted into a 64x64
		// one; subtract 16 to account for this
		C2D_DrawImageAt(
			icon, (SCREEN_WIDTH - (icon.tex->width - 16) * ICON_SCALE) / 2,
			(SCREEN_HEIGHT - (icon.tex->height - 16) * ICON_SCALE) / 2, 0,
			nullptr, ICON_SCALE, ICON_SCALE);

		versionText.draw();
	} else {
		C2D_TargetClear(this->game.getBottom(), BACKGROUND);

		gui.draw();
	}
}
