#pragma once

#include <3dstris/gui.hpp>
#include <3dstris/state.hpp>
#include <3dstris/ingame.hpp>
#include <3dstris/states/playing.hpp>

class Results : public State {
   public:
    Results(Ingame* parent);
    Results(Ingame* parent, double sprintTime);

	void update(double dt) override;
	void draw(bool bottom) override;

   private:
    Text topText;

    Ingame* parent;

	GUI gui;

	Button& restartButton;
	Button& menuButton;
};
