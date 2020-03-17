#pragma once

#include <3dstris/gui.hpp>
#include <3dstris/state.hpp>

class LoadFailed final : public State {
   public:
	enum class FailType { CONFIG, GAMES, KEYBINDS };

	LoadFailed(FailType type = FailType::CONFIG) noexcept;

	void update(double dt) noexcept override;
	void draw(bool bottom) noexcept override;

   private:
	static const char* FAILTYPE_TO_KEY[];

	Text reason;

	GUI gui;

	Button& ok;
};
