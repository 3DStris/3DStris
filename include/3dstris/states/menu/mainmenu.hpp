#pragma once

#include <3dstris/gui.hpp>
#include <3dstris/state.hpp>

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
	Button& settingsButton;
	Button& exitButton;

	Button& keybindsButton;
	Button& gamesButton;
	Button& languagesButton;
};
