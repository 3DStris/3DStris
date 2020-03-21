#pragma once

#include <3dstris/gui.hpp>
#include <3dstris/state.hpp>

class LanguageSelect final : public State {
   public:
	LanguageSelect() noexcept;

	void update(double dt) noexcept override;
	void draw(bool bottom) const noexcept override;

   private:
	Text select;

	GUI gui;

	Button& save;
	Button& cancel;
	L10n::Language language;
};
