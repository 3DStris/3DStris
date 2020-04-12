#include <3dstris/game.hpp>
#include <3dstris/gui/widgets/special/languagebutton.hpp>

LanguageButton::LanguageButton(GUI& _parent, const Pos _pos, const WH _wh,
							   L10n::Language&& language,
							   L10n::Language& toSet) noexcept
	: Button(_parent, _pos, _wh, language),
	  language(language),
	  toSet(toSet),

	  flag(C2D_SpriteSheetGetImage(Game::get().getImageSheet(),
								   L10n::getFlag(language))) {
	text.scale(wh.x, 0.635f);
	text.align(Text::Align::CENTER, Pos{pos.x + 3 + 1, pos.y},
			   WH{wh.x + (flag.tex->width - (flag.tex->width - 11)), wh.y});
}

void LanguageButton::draw() const noexcept {
	Button::draw();
	C2D_DrawImageAt(
		flag, pos.x + 3,
		pos.y + (wh.y - (flag.tex->height - (flag.tex->height - 11))) / 2, 1);
}

void LanguageButton::update(const touchPosition touch,
							const touchPosition previous) noexcept {
	Button::update(touch, previous);

	if (pressed()) {
		toSet = language;
	}
}
