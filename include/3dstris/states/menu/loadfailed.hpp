#pragma once

#include <3dstris/gui.hpp>
#include <3dstris/state.hpp>
#include <3dstris/states/game/playing.hpp>
#include <3dstris/util.hpp>

class LoadFailed : public State {
   public:
	enum class FailType { CONFIG, GAMES, KEYBINDS };

	LoadFailed(const FailType type = FailType::CONFIG);

	void update(const double dt) override;
	void draw(const bool bottom) override;

   private:
	static const char* FAILTYPE_TO_KEY[];

	Text failedText;

	GUI gui;

	Button& okButton;
};
