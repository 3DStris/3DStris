#pragma once

#include <3dstris/gui.hpp>
#include <3dstris/state.hpp>
#include <3dstris/states/playing.hpp>

class Paused : public State {
   public:
    Paused(Ingame* parent);

	void update(double dt) override;
	void draw(bool bottom) override;

   private:
	Text pausedText;

    Ingame* parent;

	GUI gui;

	Button& restartButton;
	Button& unpauseButton;
	Button& menuButton;
};
