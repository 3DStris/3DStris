#pragma once

#include <3dstris/gui.hpp>
#include <3dstris/gui/widgets/button.hpp>
#include <3dstris/gui/widgets/panel.hpp>
#include <3dstris/state.hpp>
#include <3dstris/util/text.hpp>

class KeybindButton;
class KeybindSelect final : public State {
   public:
	KeybindSelect();

	void update(double dt) override;
	void draw(bool bottom) const noexcept override;

   private:
	Text title;

	std::vector<std::reference_wrapper<KeybindButton>> buttons;
	std::vector<Text> labels;

	Keybinds::Binds binds;

	GUI gui;

	Panel tip;
	Text tipText;

	Button& save;
	Button& reset;
	Button& cancel;
};
