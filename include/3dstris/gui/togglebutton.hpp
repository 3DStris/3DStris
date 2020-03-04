#pragma once

#include <3dstris/gui/button.hpp>

class GUI;
class ToggleButton final : public Button {
   public:
	ToggleButton(GUI& parent, const Pos pos, const WH wh, sds text,
				 const bool defaultValue);
	~ToggleButton() override;

	void update(const touchPosition touch,
				const touchPosition previous) override;

	bool getValue();

   private:
	using Button::setText;

	sds text;

	bool value;
};
