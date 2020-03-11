#pragma once

#include <3dstris/gui.hpp>
#include <3dstris/state.hpp>

class MainMenu final : public State {
   public:
	MainMenu();

	void update(double dt) override;
	void draw(bool bottom) override;

   private:
	Text version;

	C2D_Image icon;

	GUI gui;

	Button& play;
	Button& settings;
	Button& exit;

	Button& games;
	Button& languages;
};
