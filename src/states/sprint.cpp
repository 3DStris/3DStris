#include <3dstris/states/mainmenu.hpp>
#include <3dstris/states/paused.hpp>
#include <3dstris/states/results.hpp>
#include <3dstris/states/sprint.hpp>

Sprint::Sprint() : Ingame(), infoText(""), time(0.0) {
	infoText.setPos(10, 10);
}

void Sprint::reset() {
	Ingame::reset();

	time = 0.0;
}

void Sprint::update(double dt) {
	u32 kDown = hidKeysDown();
	u32 kHeld = hidKeysHeld();

	if (kDown & KEY_START) {
		game.pushState(make_unique<Paused>(this));
		return;
	}

	if (piece.dead()) {
		game.pushState(make_unique<Results>(this));
		return;
	}

	time += dt;

	infoText.setText(sdscatprintf(sdsempty(), "Lines: %d\nTime: %.3f",
								  board.linesCleared(), time));

	if (board.linesCleared() >= 20) {
		game.pushState(make_unique<Results>(this, time));
		return;
	}

	Ingame::update(dt);
}

void Sprint::draw(bool bottom) {
	Ingame::draw(bottom);
	if (bottom) {
		C2D_TargetClear(this->game.getBottom(), BACKGROUND);

		infoText.draw();
	}
}
