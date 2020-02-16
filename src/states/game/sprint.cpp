#include <3dstris/states/game/paused.hpp>
#include <3dstris/states/game/results.hpp>
#include <3dstris/states/game/sprint.hpp>
#include <3dstris/states/game/sprintresults.hpp>
#include <3dstris/states/menu/mainmenu.hpp>

Sprint::Sprint()
	: Ingame(),
	  infoFormat(game.translate("sprint.info")),
	  time(0.0),
	  startTimer(0.0) {
	infoText.setPos({10, 10});
}

Sprint::~Sprint() {
	sdsfree(infoFormat);
}

void Sprint::reset() {
	Ingame::reset();

	infoText.setText(sdsempty());

	time = 0.0;
	startTimer = 0.0;
}

void Sprint::update(const double dt) {
	const u32 kDown = hidKeysDown();

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

	infoText.setText(sdscatprintf(sdsempty(), infoFormat, board.linesCleared(),
								  time, board.droppedPieces() / time));

	if (board.linesCleared() >= 20) {
		game.pushState(make_unique<SprintResults>(
			this,
			SavedGame{
				time_t((osGetTime() - 2208988800000)) /
					1000,  // why? because the 3ds counts in milliseconds.. but
						   // that's not where it ends; it also starts counting
						   // from 1900. why, Nintendo?! why would you do this?!
				time, board.droppedPieces() / time}));
		return;
	}

	Ingame::update(dt);
}

void Sprint::draw(const bool bottom) {
	Ingame::draw(bottom);
	if (bottom) {
		C2D_TargetClear(game.getBottom(), BACKGROUND);

		infoText.draw();
	}
}