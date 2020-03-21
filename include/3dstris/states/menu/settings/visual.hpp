#pragma once

#include <3dstris/gui/widgets/togglebutton.hpp>
#include <3dstris/states/menu/settings/base.hpp>

class VisualSettings final : public BaseSettings {
   public:
	VisualSettings() noexcept;

	void update(double dt) noexcept override;
	void draw(bool bottom) const noexcept override;

   private:
	Panel backTip;
	Text backTipText;

	ToggleButton& useTextures;
};
