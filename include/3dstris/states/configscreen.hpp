#pragma once

#include <3dstris/gui.hpp>
#include <3dstris/gui/panel.hpp>
#include <3dstris/gui/u32inputfield.hpp>
#include <3dstris/state.hpp>

class ConfigScreen : public State {
   public:
	ConfigScreen();

	void update(const double dt) override;
	void draw(const bool bottom) override;

   private:
	GUI gui;

	Text tipText;
	Text dasText;
	Text arrText;
	Text dropTimerText;

	Button& saveButton;
	Button& cancelButton;

	Panel& panel;
	Panel tipPanel;

	U32InputField& dasInputField;
	U32InputField& arrInputField;
	U32InputField& dropTimerInputField;

	u32 getDas() const;
	u32 getArr() const;
	u32 getDropTimer() const;
};
