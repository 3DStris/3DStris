#pragma once

#include <3dstris/gui.hpp>
#include <3dstris/state.hpp>

class ModeSelect : public State {
   public:
	ModeSelect();

	void update(const double dt) override;
	void draw(const bool bottom) override;

   private:
	Text topText;

	GUI gui;

	Button& normalButton;
	Button& sprintButton;
	Button& backButton;
};
