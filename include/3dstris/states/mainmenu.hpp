#pragma once

#include <citro2d.h>
#include <3dstris/gui.hpp>
#include <3dstris/state.hpp>
#include <3dstris/states/configscreen.hpp>
#include <3dstris/states/playing.hpp>
#include <3dstris/util.hpp>

class MainMenu : public State {
   public:
	MainMenu();

	void update(const double dt) override;
	void draw(const bool bottom) override;

   private:
	Text versionText;

	C2D_Image icon;

	GUI gui;

	Button& playButton;
	Button& optionsButton;
	Button& exitButton;
};
