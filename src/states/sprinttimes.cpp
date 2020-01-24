#include <3dstris/gui/panel.hpp>
#include <3dstris/states/sprinttimes.hpp>
#include <algorithm>
#include <iomanip>

SprintTimes::SprintTimes()
	: State(),
	  panel(gui, Pos{TABLE_X, TABLE_Y}, WH{TABLE_W, TABLE_H}, true),

	  backButton(gui.add<Button>(Pos{-1, BSCREEN_HEIGHT - 60}, WH{100, 50},
								 "Back", Button::Flags::HCENTER)),

	  timeLabel("Time"),
	  dateLabel("Date"),

	  games(game.getGames().all()),

	  titleText("Games", Pos{-1, 0}, {1.25f, 1.25f}),
	  noGamesText("You haven't played any Sprint games yet.", Pos{0, 0},
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

void SprintTimes::genValues() {
	values.clear();

	for (u32 i = 0; i < std::min(games.size(), size_t(CELLS)); ++i) {
		auto& saved = games[i + topCell];
		auto time =
			make_unique<Text>(sdscatprintf(sdsempty(), "%.3fs", saved.time));
		time->setScale({0.8f, 0.8f});
		time->align(Text::Align::CENTER,
					Pos{TABLE_X, TABLE_Y + CELL_H * (i + 1.0f)},
					WH{TIME_W, CELL_H});
		values.push_back(std::move(time));

		char dateString[60];
		saved.dateString(dateString, 60, "%F");
		auto date = make_unique<Text>(sdscatfmt(sdsempty(), "%s", dateString));
		date->setScale({0.7f, 0.7f});
		date->align(Text::Align::CENTER,
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
			text->draw();
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

void SprintTimes::updateInfoText(const SavedGame& game) {
	char date[60];
	game.dateString(date, 60);
	infoText.setText(sdscatprintf(sdsempty(),
								  "Time: %.3fs\nPPS: %.2f\nDate: %s", game.time,
								  game.pps, date));
}
