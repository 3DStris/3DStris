#pragma once

#include <3dstris/gui.hpp>
#include <3dstris/gui/integerinputfield.hpp>
#include <3dstris/gui/panel.hpp>
#include <3dstris/gui/togglebutton.hpp>
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
