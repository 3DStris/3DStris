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
	Color colBackground;

	C2D_TextBuf dynamicTextBuf;

	std::shared_ptr<Slider> slider;

	GUI gui;
};
