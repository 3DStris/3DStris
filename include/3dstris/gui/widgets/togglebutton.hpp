#pragma once

#include <3dstris/gui/widgets/button.hpp>

class GUI;
class ToggleButton final : public Button {
   public:
	ToggleButton(GUI& parent, Pos pos, WH wh, sds text,
				 bool defaultValue) noexcept;
	~ToggleButton() noexcept override;

	void update(touchPosition touch, touchPosition previous) noexcept override;

	bool getValue() const noexcept;

   private:
	using Button::setText;

	sds text;

	bool value;
};
