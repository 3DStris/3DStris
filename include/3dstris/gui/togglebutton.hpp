#pragma once

#include <3dstris/gui/button.hpp>
#include <3dstris/util/l10n.hpp>
#include <3dstris/util/text.hpp>

class GUI;
class ToggleButton : public Button {
   public:
	ToggleButton(GUI& parent, const Pos pos, const WH wh, const sds text,
				 const bool defaultValue);

	void draw() const override;
	void update(const touchPosition touch,
				const touchPosition previous) override;

	bool getValue();

   private:
	using Button::setText;

	sds text;

	bool value;
};
