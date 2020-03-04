#pragma once

#include <3dstris/gui.hpp>
#include <3dstris/state.hpp>

class ModeSelect final : public State {
   public:
	ModeSelect();

	void update(const double dt) override;
	void draw(const bool bottom) override;

   private:
	Text title;

	GUI gui;

	Button& normalButton;
	Button& sprintButton;
	Button& backButton;
};
