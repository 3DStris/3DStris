#pragma once

#include <3dstris/gui/widgets/togglebutton.hpp>
#include <3dstris/states/menu/settings/base.hpp>

class VisualSettings final : public BaseSettings {
   public:
	VisualSettings();

	void update(double dt) override;
	void draw(bool bottom) override;

   private:
	Panel backTip;
	Text backTipText;

	ToggleButton& useTextures;
};
