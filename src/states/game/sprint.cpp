#include <3dstris/states/game/paused.hpp>
#include <3dstris/states/game/results.hpp>
#include <3dstris/states/game/sprint.hpp>
#include <3dstris/states/game/sprintresults.hpp>
#include <3dstris/states/menu/mainmenu.hpp>

Sprint::Sprint(const u16 lines)
	: Ingame(),
	  infoFormat(game.translate("sprint.info")),

	  lines(lines),

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
	if (kDown & KEY_START) {
		Ingame::update(dt);
		return;
	}

	if (board.linesCleared() >= lines) {
		game.pushState(make_unique<SprintResults>(
			this,
			SavedGame{time, board.droppedPieces() / time,
					  // osGetTime() returns milliseconds
					  // since 1/1/1900. We divide by 1000
					  // and subtract the difference from
					  // 1/1/1900 to 1/1/1970 to have the
					  // timestamp be in seconds and in
					  // Unix time (epoch), respectively
					  static_cast<time_t>(osGetTime() / 1000 - 2208988800),
					  lines}));
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
