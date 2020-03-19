#pragma once

extern "C" {
#include <c2d/base.h>
}

using Color = u32;

struct Theme final {
	static constexpr Color WHITE = C2D_Color32(255, 255, 255, 255);
	static constexpr Color BLACK = C2D_Color32(0, 0, 0, 255);

	Color background;
	Color text;

	Color button;
	Color buttonOutline;
	Color buttonHeld;

	Color inputField;
	Color inputFieldHeld;

	Color panel;
	Color panelOutline;

	Color board;
	Color grid;

	static Theme night() noexcept;
};
