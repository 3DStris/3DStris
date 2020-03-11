#include <3dstris/gui/widgets/special/languagebutton.hpp>
#include <3dstris/states/menu/languageselect.hpp>
#include <3dstris/states/menu/mainmenu.hpp>

LanguageSelect::LanguageSelect()
	: State(),
	  selectText(game.translate("languageselect.select")),

	  saveButton(gui.add<Button>(Pos{10, BSCREEN_HEIGHT - 50}, WH{75, 40},
								 game.translate("save"))),
	  cancelButton(gui.add<Button>(Pos{BSCREEN_WIDTH - 90, BSCREEN_HEIGHT - 50},
								   WH{80, 40}, game.translate("cancel"))),
	  language(game.getConfig().language) {
	selectText.align(Text::Align::SCREEN_CENTER);

	float y = 10;
	float x = 10;
	for (const auto& lang : L10n::LANGUAGES) {
		gui.add<LanguageButton>(Pos{x, y}, WH{80, 25}, lang, language);

		y += 25 + 10;
		if (y + 35 + 25 > SCREEN_HEIGHT) {
			y = 10;
			x += 80 + 10;
		}
	}
}

void LanguageSelect::update(const double dt) {
	gui.update(dt);

	if (saveButton.pressed()) {
		if (language != game.getConfig().language) {
			game.getL10n().loadLanguage(language);

			auto& config = game.getConfig();
			config.language = language;
			config.save();
		}

		game.setState(make_unique<MainMenu>());
		return;
	}

	if (cancelButton.pressed() || hidKeysUp() & KEY_B) {
		game.popState();
	}
}

void LanguageSelect::draw(const bool bottom) {
	if (!bottom) {
		C2D_TargetClear(game.getTop(), gui.getTheme().background);

		selectText.draw();
	} else {
		C2D_TargetClear(game.getBottom(), gui.getTheme().background);

		gui.draw();
	}
}
