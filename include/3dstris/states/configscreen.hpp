#pragma once

#include <3dstris/gui.hpp>
#include <3dstris/gui/panel.hpp>
#include <3dstris/gui/togglebutton.hpp>
#include <3dstris/gui/u32inputfield.hpp>
#include <3dstris/state.hpp>

class ConfigScreen : public State {
   public:
	ConfigScreen();

	void update(const double dt) override;
	void draw(const bool bottom) override;

   private:
	GUI gui;

	Text title;
	Text tipText;

	Text dasText;
	Text arrText;
	Text dropTimerText;

	Button& save;
	Button& cancel;

	Panel& panel;
	Panel tip;

	U32InputField& das;
	U32InputField& arr;
	U32InputField& dropTimer;

	ToggleButton& useTextures;
};
