#pragma once

#include <3dstris/gui.hpp>
#include <3dstris/state.hpp>

class LanguageSelect final : public State {
   public:
	LanguageSelect();

	void update(double dt) override;
	void draw(bool bottom) override;

   private:
	Text selectText;

	GUI gui;

	Button& saveButton;
	Button& cancelButton;
	L10n::Language language;
};
