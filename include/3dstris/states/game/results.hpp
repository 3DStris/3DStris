#pragma once

#include <3dstris/gui.hpp>
#include <3dstris/state.hpp>
#include <3dstris/states/game/ingame.hpp>

class Results final : public State {
   public:
	explicit Results(Ingame* parent);

	void update(const double dt) override;
	void draw(const bool bottom) override;

   protected:
	static constexpr Color RESULTS = C2D_Color32(0, 0, 0, 190);

	Ingame* parent;

	Text deadText;

	GUI gui;

	Button& restartButton;
	Button& menuButton;
};
