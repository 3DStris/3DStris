#pragma once

#include <3dstris/gui.hpp>
#include <3dstris/state.hpp>

class KeybindButton;
class KeybindSelect : public State {
   public:
	KeybindSelect();

	void update(const double dt) override;
	void draw(const bool bottom) override;

   private:
	Text selectText;

	std::vector<std::reference_wrapper<KeybindButton>> buttons;
	std::vector<Text> labels;

	Keybinds::Binds binds;

	GUI gui;

	Button& saveButton;
	Button& cancelButton;
	L10n::Language language;
};