#pragma once

#include <3dstris/gui.hpp>

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
	Button& languagesButton;
};
