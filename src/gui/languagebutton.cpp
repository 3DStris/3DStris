#include <3dstris/game.hpp>
#include <3dstris/gui/languagebutton.hpp>

LanguageButton::LanguageButton(GUI& parent, const Pos pos, const WH wh,
							   const L10n::Language language,
							   L10n::Language& toSet)
	: Button(parent, pos, wh, L10n::languageToString(language)),
	  toSet(toSet),
	  language(language),
	  flag(C2D_SpriteSheetGetImage(Game::get().getImageSheet(),
								   L10n::getFlag(language))) {}

void LanguageButton::draw() const {
	Button::draw();
	C2D_DrawImageAt(flag, pos.x + 3,
					pos.y + (wh.y - (flag.tex->height - 53)) / 2, 1);
}

void LanguageButton::update(const touchPosition touch,
							const touchPosition previous) {
	Button::update(touch, previous);

	if (pressed()) {
		toSet = language;
	}
}
