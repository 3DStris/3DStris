#pragma once

#include <3dstris/gui/widgets/button.hpp>

class GUI;
class ToggleButton final : public Button {
   public:
	ToggleButton(GUI& parent, Pos pos, WH wh, sds text, bool defaultValue);
	~ToggleButton() override;

	void update(touchPosition touch, touchPosition previous) override;

	bool getValue();

   private:
	using Button::setText;

	sds text;

	bool value;
};
