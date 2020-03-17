#pragma once

#include <3dstris/gui.hpp>
#include <3dstris/state.hpp>

class SprintSelect final : public State {
   public:
	SprintSelect() noexcept;

	void update(double dt) noexcept override;
	void draw(bool bottom) noexcept override;

   private:
	Text title;

	GUI gui;

	Button& twenty;
	Button& forty;
	Button& custom;

	Button& back;
};
