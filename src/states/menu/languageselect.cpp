#include <3dstris/gui/widgets/special/languagebutton.hpp>
#include <3dstris/states/menu/languageselect.hpp>
#include <3dstris/states/menu/mainmenu.hpp>

LanguageSelect::LanguageSelect() noexcept
	: State(),
	  select(game.translate("languageselect.select")),

	  save(gui.add<Button>(Pos(10, gui.getHeight() - 50), WH{75, 40},
						   game.translate("save"))),
	  cancel(gui.add<Button>(Pos(gui.getWidth() - 90, gui.getHeight() - 50),
							 WH{80, 40}, game.translate("cancel"))),
	  language(game.getConfig().language) {
	select.align(Text::Align::SCREEN_CENTER);

	float y = 10;
	float x = 10;
	for (auto& lang : L10n::getCodes()) {
		gui.add<LanguageButton>(Pos{x, y}, WH{80, 25}, std::move(lang),
								language);

		y += 25 + 10;
		if (y + 35 + 25 > gui.getHeight()) {
			y = 10;
			x += 80 + 10;
		}
	}
}

void LanguageSelect::update(const double dt) noexcept {
	gui.update(dt);

	if (save.pressed()) {
		if (!(language == game.getConfig().language)) {
			game.loadLanguage(language);

			auto& config = game.getConfig();
			config.language = language;
			config.save();
		}

		game.setState(make_unique<MainMenu>());
		return;
	}

	if (cancel.pressed() || hidKeysUp() & KEY_B) {
		game.popState();
	}
}

void LanguageSelect::draw(const bool bottom) const noexcept {
	if (!bottom) {
		C2D_TargetClear(game.getTop(), gui.getTheme().background);

		select.draw();
	} else {
		C2D_TargetClear(game.getBottom(), gui.getTheme().background);

		gui.draw();
	}
}
