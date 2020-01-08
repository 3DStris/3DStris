#pragma once

#include <3dstris/gui.hpp>
#include <3dstris/state.hpp>
#include <3dstris/states/playing.hpp>

class Results : public State {
   public:
	Results(State* parent);

	void update(double dt) override;
	void draw(bool bottom) override;

   private:
	Color colBackground;

	Text deadText;

	State* parent;

	GUI gui;

	Button& restartButton;
	Button& menuButton;
};
