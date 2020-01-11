#pragma once

#include <3dstris/gui.hpp>
#include <3dstris/state.hpp>
#include <3dstris/states/playing.hpp>

class Results : public State {
   public:
	Results(Ingame* parent);
	Results(Ingame* parent, const double sprintTime);

	void update(const double dt) override;
	void draw(const bool bottom) override;

   private:
	static constexpr Color RESULTS = C2D_Color32(0, 0, 0, 190);

	Text deadText;

	Ingame* parent;

	GUI gui;

	Button& restartButton;
	Button& menuButton;
};
