#pragma once

#include <3dstris/gui/widgets/button.hpp>
#include <3dstris/states/game/ingame.hpp>

class SprintResults final : public State {
   public:
	SprintResults(Ingame* parent, SavedGame&& saved);

	void update(double dt) override;
	void draw(bool bottom) const override;

   private:
	static constexpr Color RESULTS = C2D_Color32(0, 0, 0, 190);

	Ingame* parent;

	const String timeFormat;
	Text timeText;

	GUI gui;

	Button& restart;
	Button& times;
	Button& menu;
};
