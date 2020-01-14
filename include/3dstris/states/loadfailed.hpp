#pragma once

#include <3dstris/gui.hpp>
#include <3dstris/state.hpp>
#include <3dstris/states/playing.hpp>
#include <3dstris/util.hpp>

class LoadFailed : public State {
   public:
	enum FailType { CONFIG, GAMES };

	LoadFailed(const FailType type = CONFIG);

	void update(const double dt) override;
	void draw(const bool bottom) override;

   private:
	Text failedText;

	GUI gui;

	Button& okButton;
};