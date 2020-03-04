#pragma once

#include <3dstris/gui.hpp>
#include <3dstris/states/game/ingame.hpp>

class Paused final : public State {
   public:
	Paused(Ingame* parent);

	void update(const double dt) override;
	void draw(const bool bottom) override;

   private:
	static constexpr Color PAUSED = C2D_Color32(0, 0, 0, 190);

	Ingame* parent;

	Text pausedText;

	GUI gui;

	Button& restartButton;
	Button& unpauseButton;
	Button& menuButton;
};
