#pragma once

#include <3dstris/gui/widgets/button.hpp>

class GUI;
class ToggleButton final : public Button {
   public:
	ToggleButton(GUI& parent, Pos pos, WH wh, String&& text,
				 bool defaultValue) noexcept;

	void update(touchPosition touch, touchPosition previous) noexcept override;

	bool getValue() const noexcept;

   private:
	using Button::setText;

	String text;

	bool value;
};
