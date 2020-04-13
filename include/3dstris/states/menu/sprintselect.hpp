#pragma once

#include <3dstris/gui/widgets/button.hpp>
#include <3dstris/state.hpp>

class SprintSelect final : public State {
   public:
	SprintSelect() noexcept;

	void update(double dt) noexcept override;
	void draw(bool bottom) const noexcept override;

   private:
	Text title;

	GUI gui;

	Button& twenty;
	Button& forty;
	Button& custom;

	Button& back;
};
