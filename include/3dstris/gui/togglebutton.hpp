#pragma once

#include <3dstris/gui/button.hpp>

class GUI;
class ToggleButton : public Button {
   public:
	ToggleButton(GUI& parent, const Pos pos, const WH wh, const sds text,
				 const bool defaultValue);
	~ToggleButton();

	void update(const touchPosition touch,
				const touchPosition previous) override;

	bool getValue();

   private:
	using Button::setText;

	sds text;

	bool value;
};
