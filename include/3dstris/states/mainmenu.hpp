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
	static constexpr u8 ICON_SCALE = 3;

	Text versionText;

	C2D_Image icon;

	GUI gui;

	Button& playButton;
	Button& settingsButton;
	Button& exitButton;
	Button& gamesButton;
};
