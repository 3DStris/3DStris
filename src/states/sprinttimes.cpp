#include <3dstris/game.hpp>
#include <3dstris/states/sprinttimes.hpp>

SprintTimes::SprintTimes()
	: State(),
	  infoFormat(game.translate("sprint.times.info")),

	  panel(gui, Pos{TABLE_X, TABLE_Y}, WH{TABLE_W, TABLE_H}, true),

	  backButton(gui.add<Button>(Pos{-1, BSCREEN_HEIGHT - 60}, WH{100, 50},
								 game.translate("back"),
								 Button::Flags::HCENTER)),

	  timeLabel(game.translate("sprint.times.table.time")),
	  dateLabel(game.translate("sprint.times.table.date")),

	  games(game.getGames().all()),

	  titleText(game.translate("results.sprint.times"), Pos{0, 5}),
	  noGamesText(game.translate("sprint.times.nogames"), Pos{0, 0},
				  {0.75f, 0.75f}),
	  infoText(sdsempty(), Pos{10, 10}, {0.8f, 0.8f}),
	  selectedText(sdsempty(), Pos{-1, SCREEN_HEIGHT - TABLE_Y + 10},
				   {0.65f, 0.65f}) {
	timeLabel.align(Text::Align::CENTER, Pos{TABLE_X, TABLE_Y},
					WH{TIME_W, CELL_H});
	dateLabel.align(Text::Align::CENTER, Pos{TABLE_X + TIME_W, TABLE_Y},
					WH{DATE_W, CELL_H});
	genValues();

	titleText.align(Text::Align::HCENTER, Pos{0, 0},
					{SCREEN_WIDTH, SCREEN_HEIGHT});
	noGamesText.align(Text::Align::SCREEN_CENTER);
	updateInfoText(games[selected]);
	updateSelectedText();
}

SprintTimes::~SprintTimes() {
	sdsfree(infoFormat);
}

void SprintTimes::genValues() {
	values.clear();

	for (u32 i = 0; i < std::min(games.size(), size_t(CELLS)); ++i) {
		auto& saved = games[i + topCell];
		Text time(sdscatprintf(sdsempty(), "%.3fs", saved.time), Pos{},
				  {0.8f, 0.8f});
		time.align(Text::Align::CENTER,
				   Pos{TABLE_X, TABLE_Y + CELL_H * (i + 1.0f)},
				   WH{TIME_W, CELL_H});
		values.push_back(std::move(time));

		sds dateString = sdsnewlen("", 40);
		saved.dateString(dateString, 40, "%F");
		Text date(dateString, Pos{}, {0.7f, 0.7f});
		date.align(Text::Align::CENTER,
				   Pos{TABLE_X + TIME_W, TABLE_Y + CELL_H * (i + 1.0f)},
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

	if (games.empty()) {
		return;
	}

	auto kDown = hidKeysDown();
	if (kDown & KEY_DOWN) {
		if (selected >= games.size() - 1) {
			selected = 0;
			topCell = 0;

			genValues();
		} else {
			++selected;
			if (selected - topCell >= CELLS) {
				++topCell;
				genValues();
			}
		}

		updateInfoText(games[selected]);
		updateSelectedText();
	} else if (kDown & KEY_UP) {
		if (selected <= 0) {
			selected = games.size() - 1;
			topCell = selected - 2;

			genValues();
		} else {
			--selected;
			if (int(selected - topCell) < 0) {
				--topCell;
				genValues();
			}
		}

		updateInfoText(games[selected]);
		updateSelectedText();
	}
}

void SprintTimes::draw(const bool bottom) {
	if (!bottom) {
		C2D_TargetClear(this->game.getTop(), BACKGROUND);

		if (games.empty()) {
			noGamesText.draw();
			return;
		}

		titleText.draw();

		panel.draw();
		for (u16 i = 0; i < CELLS; ++i) {
			GUI::drawHLine(Pos{TABLE_X, TABLE_Y + CELL_H * (i + 1.0f)},
						   TABLE_W);
		}
		GUI::drawVLine(Pos{TABLE_X + TIME_W, TABLE_Y}, TABLE_H);

		timeLabel.draw();
		dateLabel.draw();

		for (const auto& text : values) {
			text.draw();
		}

		GUI::drawOutline(
			Pos{TABLE_X, TABLE_Y + CELL_H * (selected + 1.0f - topCell)},
			WH{TABLE_W, CELL_H - 2}, 2, WHITE);

		selectedText.draw();
	} else {
		C2D_TargetClear(this->game.getBottom(), BACKGROUND);

		if (!games.empty()) {
			infoText.draw();
		}
		gui.draw();
	}
}

void SprintTimes::updateSelectedText() {
	selectedText.setText(
		sdscatfmt(sdsempty(), "%u/%u", selected + 1, games.size()));
	selectedText.align(Text::Align::HCENTER, Pos{0, 0},
					   {SCREEN_WIDTH, SCREEN_HEIGHT});
}

void SprintTimes::updateInfoText(const SavedGame& savedGame) {
	char date[60];
	savedGame.dateString(date, 60);
	infoText.setText(sdscatprintf(sdsempty(), infoFormat, savedGame.time,
								  savedGame.pps, date));
}
