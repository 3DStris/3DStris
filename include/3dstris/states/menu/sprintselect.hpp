#pragma once

#include <3dstris/gui.hpp>
#include <3dstris/state.hpp>

class SprintSelect final : public State {
   public:
	SprintSelect();

	void update(const double dt) override;
	void draw(const bool bottom) override;

   private:
	Text title;

	GUI gui;

	Button& twentyButton;
	Button& fortyButton;
	Button& customButton;

	Button& backButton;
};
