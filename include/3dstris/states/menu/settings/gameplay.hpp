#pragma once

#include <3dstris/gui/widgets/integerinputfield.hpp>
#include <3dstris/states/menu/settings/base.hpp>

class GameplaySettings final : public BaseSettings {
   public:
	GameplaySettings();

	void update(double dt) override;
	void draw(bool bottom) override;

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
