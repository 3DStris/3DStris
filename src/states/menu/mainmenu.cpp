#include <3dstris/images.h>

#include <3dstris/states/menu/languageselect.hpp>
#include <3dstris/states/menu/mainmenu.hpp>
#include <3dstris/states/menu/modeselect.hpp>
#include <3dstris/states/menu/settings/gameplay.hpp>
#include <3dstris/states/menu/sprinttimes.hpp>
#include <3dstris/version.hpp>

MainMenu::MainMenu()
	: State(),
	  version(
		  sdscatfmt(sdsempty(), "v%s-%s", _3DSTRIS_VERSION, _3DSTRIS_GIT_HASH),
		  Pos{}, {0.5f, 0.5f}),

	  icon(C2D_SpriteSheetGetImage(game.getImageSheet(), images_icon_idx)),

	  play(gui.add<Button>(Pos{0, 10}, WH{100, 50},
						   game.translate("mainmenu.play"),
						   Button::Flags::HCENTER)),
	  settings(gui.add<Button>(Pos{0, 100}, WH{100, 50},
							   game.translate("mainmenu.settings"),
							   Button::Flags::HCENTER)),
	  exit(gui.add<Button>(Pos(0, gui.getHeight() - 50), WH{100, 40},
						   game.translate("exit"), Button::Flags::HCENTER)),

	  games(gui.add<Button>(Pos(10, gui.getHeight() - 40 - 10), WH{75, 40},
							game.translate("mainmenu.games"))),
	  languages(gui.add<Button>(
		  Pos(gui.getWidth() - 80 - 10, gui.getHeight() - 40 - 10), WH{75, 40},
		  game.translate("mainmenu.languages"))) {
	version.setPos({3, SCREEN_HEIGHT - version.getWH().y - 4});
}

void MainMenu::update(const double dt) {
	if (hidKeysDown() & KEY_START || exit.pressed()) {
		game.exit = true;
		return;
	}
	gui.update(dt);

	if (play.pressed()) {
		game.pushState(make_unique<ModeSelect>());
	} else if (settings.pressed()) {
		game.pushState(make_unique<GameplaySettings>());
	}

	else if (games.pressed()) {
		game.pushState(make_unique<SprintTimes>());
	} else if (languages.pressed()) {
		game.pushState(make_unique<LanguageSelect>());
	}
}

void MainMenu::draw(const bool bottom) {
	if (!bottom) {
		static constexpr u8 ICON_SCALE = 3;

		C2D_TargetClear(game.getTop(), gui.getTheme().background);

		// The 48x48 icon sprite gets converted into a 64x64/64x128 one;
		// subtract the difference of its new size and the original size to
		// account for this
		C2D_DrawImageAt(
			icon,
			(SCREEN_WIDTH -
			 (icon.tex->width - (icon.tex->width - 48)) * ICON_SCALE) /
				2,
			(SCREEN_HEIGHT -
			 (icon.tex->height - (icon.tex->height - 48)) * ICON_SCALE) /
				2,
			0, nullptr, ICON_SCALE, ICON_SCALE);

		version.draw();
	} else {
		C2D_TargetClear(game.getBottom(), gui.getTheme().background);

		gui.draw();
	}
}
