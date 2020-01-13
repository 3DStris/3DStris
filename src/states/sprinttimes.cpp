#include <3dstris/gui/panel.hpp>
#include <3dstris/states/sprinttimes.hpp>

SprintTimes::SprintTimes() : State(), timeLabel("Time"), dateLabel("Date") {
	gui.add<Panel>(Pos{TABLE_X, TABLE_Y}, WH{TABLE_W, TABLE_H}, true);
}

void SprintTimes::update(const double dt) {}

void SprintTimes::draw(const bool bottom) {
	if (!bottom) {
		C2D_TargetClear(this->game.getTop(), BACKGROUND);

		gui.draw();
	} else {
		C2D_TargetClear(this->game.getBottom(), BACKGROUND);
	}
}
