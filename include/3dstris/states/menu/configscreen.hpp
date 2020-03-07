#pragma once

#include <3dstris/gui.hpp>
#include <3dstris/gui/widgets/integerinputfield.hpp>
#include <3dstris/gui/widgets/panel.hpp>
#include <3dstris/gui/widgets/togglebutton.hpp>
#include <3dstris/state.hpp>

class ConfigScreen final : public State {
   public:
	ConfigScreen();

	void update(double dt) override;
	void draw(bool bottom) override;

   private:
	GUI gui;

	Text title;
	Text tipText;

	Text dasLabel;
	Text arrLabel;
	Text dropTimerLabel;

	Button& save;
	Button& cancel;

	Panel& panel;
	Panel tip;

	IntegerInputField<u16>& das;
	IntegerInputField<u16>& arr;
	IntegerInputField<u16>& dropTimer;

	ToggleButton& useTextures;
};
