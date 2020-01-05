#pragma once

#include <3dstris/gui.hpp>
#include <3dstris/state.hpp>
#include <3dstris/states/playing.hpp>

class Paused : public State {
   public:
	Paused();

	void update(double dt) override;
	void draw(bool bottom) override;

   private:
	GUI gui;

	Color colBackground;

	Text pausedText;

	std::shared_ptr<Button> unpauseButton;
	std::shared_ptr<Button> menuButton;
};
