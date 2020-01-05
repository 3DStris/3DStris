#pragma once

#include <citro2d.h>
#include <3dstris/gui.hpp>
#include <3dstris/state.hpp>
#include <3dstris/states/playing.hpp>
#include <3dstris/util.hpp>

class ConfigScreen : public State {
   public:
	ConfigScreen();
	virtual ~ConfigScreen() = default;

	void update(double dt) override;
	void draw(bool bottom) override;

   private:
	GUI gui;

	Color colBackground;

	Text dasText;
	Text arrText;

	std::shared_ptr<Button> saveButton;
	std::shared_ptr<Button> cancelButton;

	std::shared_ptr<Slider> dasSlider;
	std::shared_ptr<Slider> arrSlider;

	float getDas() const;
	float getArr() const;
};
