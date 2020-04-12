#pragma once

#include <3dstris/gui/widgets/button.hpp>
#include <3dstris/state.hpp>

class ModeSelect final : public State {
   public:
	ModeSelect() noexcept;

	void update(double dt) noexcept override;
	void draw(bool bottom) const noexcept override;

   private:
	Text title;

	GUI gui;

	Button& normal;
	Button& sprint;
	Button& back;
};
