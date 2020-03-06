#pragma once

#include <3dstris/gui.hpp>
#include <3dstris/state.hpp>

class ModeSelect final : public State {
   public:
	ModeSelect();

	void update(double dt) override;
	void draw(bool bottom) override;

   private:
	Text title;

	GUI gui;

	Button& normalButton;
	Button& sprintButton;
	Button& backButton;
};
