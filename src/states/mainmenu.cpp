#include <3dstris/sprites.h>
#include <3dstris/states/mainmenu.hpp>

MainMenu::MainMenu()
	: State(),
	  // icon(C2D_SpriteSheetGetImage(game.getSpriteSheet(), sprites_icon_idx)),
	  gui(BSCREEN_WIDTH, BSCREEN_HEIGHT, C2D_Color32(100, 100, 100, 255), BLACK,
		  C2D_Color32(50, 50, 50, 255)) {
	icon =
		C2D_SpriteSheetGetImage(this->game.getSpriteSheet(), sprites_icon_idx);
	colBackground = C2D_Color32(34, 34, 34, 255);

	gui.addButton(ButtonFlags::HCENTER, -1, 10, 100, 50, "Play", [this]() {
		this->game.setState(new Playing(), false, true);
	});
	gui.addButton(ButtonFlags::HCENTER, -1, BSCREEN_HEIGHT - 50, 80, 40, "Exit",
				  [this]() { this->game.exit = true; });
}

void MainMenu::update(double dt) {
	u32 kDown = hidKeysDown();

	if (kDown & KEY_START) {
		game.exit = true;
		return;
	}
	gui.update(dt);
}

void MainMenu::draw(bool bottom) {
	if (!bottom) {
		C2D_TargetClear(this->game.getTop(), colBackground);

		// The 48x48 icon sprite was converted into a 64x64
		// one; subtract 16 to account for this
		C2D_DrawImageAt(icon,
						SCREEN_WIDTH / 2.0f - (icon.tex->width - 16) * 1.5f,
						SCREEN_HEIGHT / 2.0f - (icon.tex->height - 16) * 1.5f,
						0, nullptr, 3, 3);
	} else {
		C2D_TargetClear(this->game.getBottom(), colBackground);

		gui.draw();
	}
}
