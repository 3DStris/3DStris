#include <3dstris/states/mainmenu.hpp>

MainMenu::MainMenu(Game& game)
	: State(game),
	gui(BSCREEN_WIDTH, BSCREEN_HEIGHT, C2D_Color32(100, 100, 100, 255), C2D_Color32(0, 0, 0, 255), C2D_Color32(50, 50, 50, 255)) {
	colBackground = C2D_Color32(34, 34, 34, 255);

	titleTextColor = C2D_Color32(255, 255, 255, 255);
	C2D_TextParse(&titleText, text_buf, "3DStris");
	C2D_TextOptimize(&titleText);

	gui.addButton(ButtonFlags::HCENTER, -1, 10, 100, 50, "Play", [&](){
		this->game.setState(new Playing(game));
	});
	gui.addButton(ButtonFlags::HCENTER, -1, BSCREEN_HEIGHT-50, 80, 40, "Exit", [&](){
		this->game.exit = true;
	});
}

void MainMenu::update(double dt) {
	gui.update(dt);
}

void MainMenu::draw(bool bottom) {
	if (!bottom) {
		C2D_TargetClear(this->game.getTop(), colBackground);

		float textW, textH;
		C2D_TextGetDimensions(&titleText, 1, 1, &textW, &textH);
		
		C2D_DrawText(&titleText, C2D_WithColor, SCREEN_WIDTH / 2.0f - textW / 2.0f, SCREEN_HEIGHT / 2.0f - textH / 2.0f, 0, 1, 1, titleTextColor);
	} else {
		C2D_TargetClear(this->game.getBottom(), colBackground);

		gui.draw();
	}
}