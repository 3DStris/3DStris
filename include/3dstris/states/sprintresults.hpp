#pragma once

#include <3dstris/gui.hpp>
#include <3dstris/state.hpp>
#include <3dstris/states/ingame.hpp>
#include <3dstris/util/text.hpp>

class SprintResults : public State {
   public:
	SprintResults(Ingame* parent, const SavedGame& saved);

	void update(const double dt) override;
	void draw(const bool bottom) override;

   private:
	static constexpr Color RESULTS = C2D_Color32(0, 0, 0, 190);

	Text timeText;

	Ingame* parent;

	GUI gui;

	Button& restartButton;
	Button& timesButton;
	Button& menuButton;
};
