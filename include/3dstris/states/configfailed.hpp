#pragma once

#include <3dstris/gui.hpp>
#include <3dstris/state.hpp>
#include <3dstris/states/playing.hpp>
#include <3dstris/util.hpp>

class ConfigFailed : public State {
   public:
	ConfigFailed();

	void update(const double dt) override;
	void draw(const bool bottom) override;

   private:
	Text failedText;

	GUI gui;

	Button& okButton;
};
