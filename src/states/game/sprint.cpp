#include <3dstris/states/game/paused.hpp>
#include <3dstris/states/game/results.hpp>
#include <3dstris/states/game/sprint.hpp>
#include <3dstris/states/game/sprintresults.hpp>
#include <3dstris/states/menu/mainmenu.hpp>
#include <ctime>

Sprint::Sprint(const u16 lines)
	: Ingame(),
	  infoFormat(game.translate("sprint.info")),

	  lines(lines),

	  time(0.0),
	  startTimer(0.0) {
	infoText.setPos({10, 10});
}

void Sprint::reset() {
	Ingame::reset();

	infoText.setText(String::empty());

	time = 0.0;
	startTimer = 0.0;
}

void Sprint::update(const double dt) {
	const u32 kDown = hidKeysDown();
	if (kDown & KEY_SELECT) {
		reset();
		return;
	}
	if (kDown & KEY_START) {
		Ingame::update(dt);
		return;
	}

	if (board.linesCleared() >= lines) {
		game.pushState(make_unique<SprintResults>(
			this, SavedGame{time, board.droppedPieces() / time,
							std::time(nullptr), lines}));
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
								  lines, time, board.droppedPieces() / time));

	Ingame::update(dt);
}

void Sprint::draw(const bool bottom) {
	Ingame::draw(bottom);
	if (bottom) {
		C2D_TargetClear(game.getBottom(), game.getTheme().background);

		infoText.draw();
	}
}
