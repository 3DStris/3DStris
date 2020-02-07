#include <3dstris/gui/languagebutton.hpp>
#include <3dstris/states/languages.hpp>
#include <3dstris/states/mainmenu.hpp>
#include <algorithm>

LanguageSelect::LanguageSelect()
	: State(),
	  selectText(game.translate("languageselect.select")),

	  saveButton(gui.add<Button>(Pos{10, BSCREEN_HEIGHT - 50}, WH{75, 40},
								 game.translate("save"))),
	  cancelButton(gui.add<Button>(Pos{BSCREEN_WIDTH - 90, BSCREEN_HEIGHT - 50},
								   WH{80, 40}, game.translate("cancel"))) {
	selectText.align(Text::Align::SCREEN_CENTER);

	float y = 10;
	float x = 10;
	for (const auto& lang : L10n::LANGUAGE_TO_STRING) {
		gui.add<LanguageButton>(Pos{x, y}, WH{80, 25}, lang.first, language);

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
		C2D_TargetClear(this->game.getTop(), BACKGROUND);

		selectText.draw();
	} else {
		C2D_TargetClear(this->game.getBottom(), BACKGROUND);

		gui.draw();
	}
}
