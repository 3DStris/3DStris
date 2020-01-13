#include <3dstris/gui/panel.hpp>
#include <3dstris/states/sprinttimes.hpp>
#include <algorithm>

SprintTimes::SprintTimes()
	: State(),
	  timeLabel("Time"),
	  dateLabel("Date"),
	  games(this->game.getGames().all()),
	  panel(gui, Pos{TABLE_X, TABLE_Y}, WH{TABLE_W, TABLE_H}, true),
	  backButton(gui.add<Button>(Pos{-1, BSCREEN_HEIGHT - 60}, WH{100, 50},
								 "Back", Button::Flags::HCENTER)) {
	timeLabel.align(Text::Align::CENTER, Pos{TABLE_X, TABLE_Y},
					WH{TIME_W, CELL_H});
	dateLabel.align(Text::Align::CENTER, Pos{TABLE_X + TIME_W, TABLE_Y},
					WH{DATE_W, CELL_H});
	std::sort(
		games.begin(), games.end(),
		[](const SavedGame& a, const SavedGame& b) { return a.time < b.time; });
	genValues();
	infoText.setScale({0.8f, 0.8f});
	infoText.setPos(Pos{10, 10});
}

void SprintTimes::genValues() {
	values.clear();
	u32 s = static_cast<u32>(games.size());
	u32 ss = s < CELLS ? s : CELLS;
	for (u32 i = 0; i < ss; ++i) {
		auto& saved = games[i + topCell];
		auto time =
			make_unique<Text>(sdscatprintf(sdsempty(), "%.3fs", saved.time));
		time->setScale({0.8f, 0.8f});
		time->align(Text::Align::CENTER,
					Pos{TABLE_X, TABLE_Y + CELL_H * (i + 1)},
					WH{TIME_W, CELL_H});
		values.push_back(std::move(time));

		auto date =
			make_unique<Text>(sdscatprintf(sdsempty(), "%lu", saved.date));
		date->setScale({0.7f, 0.7f});
		date->align(Text::Align::CENTER,
					Pos{TABLE_X + TIME_W, TABLE_Y + CELL_H * (i + 1)},
					WH{DATE_W, CELL_H});
		values.push_back(std::move(date));
	}
}

void SprintTimes::update(const double dt) {
	gui.update(dt);

	if (backButton.pressed()) {
		this->game.popState();
		return;
	}

	auto kDown = hidKeysDown();

	if (kDown & KEY_DOWN) {
		if (selected >= this->game.getGames().all().size() - 1)
			return;
		++selected;
		if (selected - topCell >= CELLS) {
			++topCell;
			genValues();
		}
	} else if (kDown & KEY_UP) {
		if (selected <= 0)
			return;
		--selected;
		if (int(selected) - int(topCell) < 0) {
			--topCell;
			genValues();
		}
	}

	auto& selectedGame = games[selected];

	infoText.setText(
		sdscatprintf(sdsempty(), "Time: %.3fs\nPPS: %.2f\nDate: %lu",
					 selectedGame.time, selectedGame.pps, selectedGame.date));
}

void SprintTimes::draw(const bool bottom) {
	if (!bottom) {
		C2D_TargetClear(this->game.getTop(), BACKGROUND);

		panel.draw();
		for (u32 i = 0; i < CELLS; ++i) {
			GUI::drawHLine(Pos{TABLE_X, TABLE_Y + CELL_H * (i + 1)}, TABLE_W);
		}
		GUI::drawVLine(Pos{TABLE_X + TIME_W, TABLE_Y}, TABLE_H);

		timeLabel.draw();
		dateLabel.draw();

		for (auto& text : values) {
			text->draw();
		}

		GUI::drawOutline(
			Pos{TABLE_X, TABLE_Y + CELL_H * (selected + 1 - topCell)},
			WH{TABLE_W, CELL_H}, 2, WHITE);
	} else {
		C2D_TargetClear(this->game.getBottom(), BACKGROUND);

		infoText.draw();
		gui.draw();
	}
}
