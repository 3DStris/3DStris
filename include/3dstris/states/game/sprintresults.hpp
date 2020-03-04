#pragma once

#include <3dstris/gui.hpp>
#include <3dstris/states/game/ingame.hpp>

class SprintResults final : public State {
   public:
	SprintResults(Ingame* parent, SavedGame&& saved);
	~SprintResults() override;

	void update(const double dt) override;
	void draw(const bool bottom) override;

   private:
	static constexpr Color RESULTS = C2D_Color32(0, 0, 0, 190);

	Ingame* parent;

	const sds timeFormat;
	Text timeText;

	GUI gui;

	Button& restartButton;
	Button& timesButton;
	Button& menuButton;
};
