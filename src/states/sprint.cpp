#include <3dstris/states/mainmenu.hpp>
#include <3dstris/states/paused.hpp>
#include <3dstris/states/results.hpp>
#include <3dstris/states/sprint.hpp>
#include <3dstris/states/sprintresults.hpp>

Sprint::Sprint() : Ingame(), time(0.0) {
	infoText.setPos({10, 10});
}

void Sprint::reset() {
	Ingame::reset();

	infoText.setText(sdsempty());

	time = 0.0;
	startTimer = 0.0;
}

void Sprint::update(const double dt) {
	u32 kDown = hidKeysDown();

	if (kDown & KEY_START) {
		game.pushState(make_unique<Paused>(this));
		return;
	}

	if (kDown & KEY_SELECT) {
		reset();
		return;
	}

	if (piece.dead()) {
		game.pushState(make_unique<Results>(this));
		return;
	}

	if (startTimer < startTime) {
		startTimer += dt;
		return;
	}

	time += dt;

	infoText.setText(
		sdscatprintf(sdsempty(), "Lines: %d\nTime: %.3fs\nPPS: %.3f",
					 board.linesCleared(), time, board.droppedPieces() / time));

	if (board.linesCleared() >= 20) {
		game.pushState(make_unique<SprintResults>(
			this,
			SavedGame{
				time_t((osGetTime() - 2208988800000)) /
					1000,  // why? because the 3ds counts in milliseconds.. but
						   // that's not where it ends; it also starts from
						   // 1900! why, Nintendo?! why?!
				time, board.droppedPieces() / time}));
		return;
	}

	Ingame::update(dt);
}

void Sprint::draw(const bool bottom) {
	Ingame::draw(bottom);
	if (bottom) {
		C2D_TargetClear(this->game.getBottom(), BACKGROUND);

		infoText.draw();
	}
}
