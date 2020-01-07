#pragma once

#include <3dstris/gui.hpp>
#include <3dstris/state.hpp>

class ConfigScreen : public State {
   public:
	ConfigScreen();

	void update(double dt) override;
	void draw(bool bottom) override;

   private:
	GUI gui;

	Color colBackground;

	Text dasText;
	Text arrText;

	Button& saveButton;
	Button& cancelButton;

	DoubleInputField& dasInputField;
	DoubleInputField& arrInputField;

	double getDas() const;
	double getArr() const;
};
