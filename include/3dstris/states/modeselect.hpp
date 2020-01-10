#pragma once

#include <3dstris/gui.hpp>
#include <3dstris/state.hpp>
#include <3dstris/states/configscreen.hpp>
#include <3dstris/states/playing.hpp>
#include <3dstris/util.hpp>

class ModeSelect : public State {
   public:
	ModeSelect();

	void update(double dt) override;
	void draw(bool bottom) override;

   private:
	Text topText;

	GUI gui;

	Button& normalButton;
	Button& sprintButton;
	Button& backButton;
};
