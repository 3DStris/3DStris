#include <3dstris/sprites.h>
#include <3dstris/states/configscreen.hpp>
#include <3dstris/states/mainmenu.hpp>
#include <3dstris/util.hpp>
#include <3dstris/version.hpp>

MainMenu::MainMenu()
	: State(),
	  versionText(
		  sdscatfmt(sdsempty(), "v%s-%s", _3DSTRIS_VERSION, _3DSTRIS_GIT_HASH),
		  WHITE),
	  icon(C2D_SpriteSheetGetImage(game.getSpriteSheet(), sprites_icon_idx)),
	  gui(BSCREEN_WIDTH, BSCREEN_HEIGHT, C2D_Color32(100, 100, 100, 255), WHITE,
		  C2D_Color32(50, 50, 50, 255)) {
	colBackground = C2D_Color32(34, 34, 34, 255);

	versionText.setScale({0.5f, 0.5f});
	versionText.setPos({3, SCREEN_HEIGHT - versionText.getWH().y / 1.25f - 5});

	playButton = gui.addButton(ButtonFlags::HCENTER, -1, 10, 100, 50, "Play");
	configButton =
		gui.addButton(ButtonFlags::HCENTER, -1, 100, 100, 50, "Config");
	exitButton = gui.addButton(ButtonFlags::HCENTER, -1, BSCREEN_HEIGHT - 50,
							   80, 40, "Exit");
}
void MainMenu::update(double dt) {
	u32 kDown = hidKeysDown();

	if (kDown & KEY_START) {
		this->game.exit = true;
		return;
	}
	gui.update(dt);

	if (playButton->pressed()) {
		this->game.pushState(make_unique<Playing>(), false, true);
		return;
	}

	if (configButton->pressed()) {
		this->game.pushState(make_unique<ConfigScreen>());
		return;
	}

	if (exitButton->pressed()) {
		this->game.exit = true;
	}
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

		versionText.draw();
	} else {
		C2D_TargetClear(this->game.getBottom(), colBackground);

		gui.draw();
	}
}
