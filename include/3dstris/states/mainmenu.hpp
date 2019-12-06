#pragma once

#include <citro2d.h>
#include <3dstris/gui.hpp>
#include <3dstris/state.hpp>
#include <3dstris/states/playing.hpp>
#include <3dstris/util.hpp>

class MainMenu : public State {
   public:
    MainMenu();

    void update(double dt) override;
    void draw(bool bottom) override;

   private:
	C2D_Text titleText;
	Color titleTextColor;
	Color colBackground;

	GUI gui;
};
