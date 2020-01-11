#pragma once

#include <3dstris/gui.hpp>
#include <3dstris/state.hpp>
#include <3dstris/states/playing.hpp>

class Paused : public State {
   public:
	Paused(State* parent);

	void update(const double dt) override;
	void draw(const bool bottom) override;

   private:
	static constexpr Color PAUSED = C2D_Color32(0, 0, 0, 190);

	Text pausedText;

	State* parent;

	GUI gui;

	Button& restartButton;
	Button& unpauseButton;
	Button& menuButton;
};
