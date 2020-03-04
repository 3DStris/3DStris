#pragma once

#include <3dstris/config/l10n.hpp>
#include <3dstris/gui/button.hpp>

class LanguageButton final : public Button {
   public:
	LanguageButton(GUI& parent, const Pos pos, const WH wh,
				   const L10n::Language language, L10n::Language& toSet);

	void setText(sds text) = delete;

	void draw() const override;
	void update(const touchPosition touch,
				const touchPosition previous) override;

   private:
	L10n::Language language;
	L10n::Language& toSet;

	C2D_Image flag;
};
