#pragma once

#include <3dstris/gui/widgets/integerinputfield.hpp>
#include <3dstris/states/menu/settings/base.hpp>

class GameplaySettings final : public BaseSettings {
   public:
	GameplaySettings() noexcept;

	void update(double dt) noexcept override;
	void draw(bool bottom) noexcept override;

   private:
	Text dasLabel;
	Text arrLabel;
	Text dropTimerLabel;

	Panel nextTip;
	Text nextTipText;

	IntegerInputField<u16>& das;
	IntegerInputField<u16>& arr;
	IntegerInputField<u16>& dropTimer;

	Button& keybinds;
};
