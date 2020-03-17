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

	static Theme night() {
		Theme night;
		night.background = C2D_Color32(20, 21, 31, 255);
		night.text = C2D_Color32(230, 230, 230, 255);

		night.button = C2D_Color32(33, 34, 48, 255);
		night.buttonOutline = C2D_Color32(35, 36, 51, 255);
		night.buttonHeld = C2D_Color32(26, 27, 38, 255);

		night.inputField = C2D_Color32(30, 32, 47, 255);
		night.inputFieldHeld = C2D_Color32(28, 30, 44, 255);

		night.panel = C2D_Color32(35, 37, 55, 255);
		night.panelOutline = C2D_Color32(37, 39, 58, 255);

		night.board = C2D_Color32(40, 42, 62, 255);
		night.grid = C2D_Color32(50, 52, 72, 100);

		return night;
	}
};
