#pragma once

#include <3dstris/gui.hpp>
#include <3dstris/state.hpp>

class SprintSelect final : public State {
   public:
	SprintSelect();

	void update(double dt) override;
	void draw(bool bottom) override;

   private:
	Text title;

	GUI gui;

	Button& twenty;
	Button& forty;
	Button& custom;

	Button& back;
};
