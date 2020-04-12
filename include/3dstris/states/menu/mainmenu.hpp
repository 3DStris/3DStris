#pragma once

#include <3dstris/gui/widgets/button.hpp>
#include <3dstris/state.hpp>

class MainMenu final : public State {
   public:
	MainMenu() noexcept;

	void update(double dt) noexcept override;
	void draw(bool bottom) const noexcept override;

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
