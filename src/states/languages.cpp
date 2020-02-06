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

	// TODO: this piece of shit will eventually break (buttons will go off the
	// screen), needs a scrollable version
	float y = 15;
	for (const auto& lang : L10n::LANGUAGE_TO_STRING) {
		gui.add<LanguageButton>(Pos{-1, y}, WH{80, 25}, lang.first, language);
		y += 35;
	}
}

void LanguageSelect::update(const double dt) {
	gui.update(dt);

	if (saveButton.pressed()) {
		if (language != game.getConfig().language) {
			auto& config = game.getConfig();
			config.getL10n().loadLanguage(language);

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
