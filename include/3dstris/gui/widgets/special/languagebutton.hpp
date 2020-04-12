#pragma once

#include <3dstris/config/l10n.hpp>
#include <3dstris/gui/widgets/button.hpp>

class LanguageButton final : public Button {
   public:
	LanguageButton(GUI& parent, Pos pos, WH wh, L10n::Language&& language,
				   L10n::Language& toSet) noexcept;

	void draw() const noexcept override;
	void update(touchPosition touch, touchPosition previous) noexcept override;

   private:
	using Button::setText;

	L10n::Language language;
	L10n::Language& toSet;

	C2D_Image flag;
};
