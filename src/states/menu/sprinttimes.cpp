#include <3dstris/states/menu/sprinttimes.hpp>

SprintTimes::SprintTimes()
	: State(),
	  infoFormat(game.translate("sprint.times.info")),

	  panel(gui, Pos{TABLE_X, TABLE_Y}, WH{TABLE_W, TABLE_H}, true),

	  back(gui.add<Button>(Pos(0, gui.getHeight() - 50), WH{100, 40},
						   game.translate("back"), Button::Flags::HCENTER)),

	  timeLabel(game.translate("sprint.times.table.time")),
	  dateLabel(game.translate("sprint.times.table.date")),
	  linesLabel(game.translate("sprint.times.table.lines")),

	  title(game.translate("results.sprint.times"), Pos{0, 5}),
	  noGames(game.translate("sprint.times.nogames"), Pos{}, {0.75f, 0.75f}),
	  page(String::empty(), Pos{10, 10}, {0.8f, 0.8f}),
	  selectedText(String::empty(), Pos{0, SCREEN_HEIGHT - TABLE_Y + 10},
				   {0.65f, 0.65f}) {
	// Games::all joins the load thread
	if (game.getGames().all().empty()) {
		noGames.align(Text::Align::SCREEN_CENTER);
		return;
	}

	games = game.getGames().all();
	std::sort(games.begin(), games.end(), std::less<SavedGame>());

	title.align(Text::Align::HCENTER, Pos{}, WH{SCREEN_WIDTH, SCREEN_HEIGHT});

	timeLabel.scale(TIME_W, 1.0f);
	timeLabel.align(Text::Align::CENTER, Pos{TABLE_X, TABLE_Y},
					WH{TIME_W, CELL_H});

	dateLabel.scale(DATE_W, 1.0f);
	dateLabel.align(Text::Align::CENTER, Pos{TABLE_X + TIME_W, TABLE_Y},
					WH{DATE_W, CELL_H});

	linesLabel.scale(LINES_W, 1.0f);
	linesLabel.align(Text::Align::CENTER,
					 Pos{TABLE_X + DATE_W + TIME_W, TABLE_Y},
					 WH{LINES_W, CELL_H});

	genValues();

	updateInfoText(games[selected]);
	updateSelectedText();
}

void SprintTimes::genValues() {
	values.clear();

	for (u32 i = 0; i < std::min(games.size(), CELLS); ++i) {
		const SavedGame& saved = games[i + topCell];

		Text time(String::fromPrintf("%.3fs", saved.time), Pos{}, {0.8f, 0.8f});
		time.align(Text::Align::CENTER,
				   Pos{TABLE_X, TABLE_Y + CELL_H * (i + 1.0f)},
				   WH{TIME_W, CELL_H});
		values.push_back(std::move(time));

		// why sds? because the Text i pass it to later will allocate
		// a new sds if i pass a regular, stack-allocated char array anyways
		sds dateString = sdsnewlen(nullptr, 40);
		saved.dateString(dateString, 40, "%F");
		Text date(dateString, Pos{}, {0.7f, 0.7f});
		date.align(Text::Align::CENTER,
				   Pos{TABLE_X + TIME_W, TABLE_Y + CELL_H * (i + 1.0f)},
				   WH{DATE_W, CELL_H});
		values.push_back(std::move(date));

		Text lines(sdsfromlonglong(saved.lines), Pos{}, {0.7f, 0.7f});
		lines.align(
			Text::Align::CENTER,
			Pos{TABLE_X + TIME_W + DATE_W, TABLE_Y + CELL_H * (i + 1.0f)},
			WH{LINES_W, CELL_H});
		values.push_back(std::move(lines));
	}
}

void SprintTimes::update(const double dt) {
	gui.update(dt);

	const u32 kDown = hidKeysDown();
	if (back.pressed() || kDown & KEY_B) {
		game.popState();
		return;
	}

	if (games.empty()) {
		return;
	}
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
			if (static_cast<int>(selected - topCell) < 0) {
				--topCell;
				genValues();
			}
		}

		updateInfoText(games[selected]);
		updateSelectedText();
	}
}

void SprintTimes::draw(const bool bottom) const noexcept {
	if (!bottom) {
		C2D_TargetClear(game.getTop(), gui.getTheme().background);

		if (games.empty()) {
			noGames.draw();
			return;
		}

		title.draw();

		panel.draw();
		for (u16 i = 0; i < CELLS; ++i) {
			GUI::drawHLine(Pos{TABLE_X, TABLE_Y + CELL_H * (i + 1.0f)}, TABLE_W,
						   2, gui.getTheme().grid);
		}
		GUI::drawVLine(Pos{TABLE_X + TIME_W, TABLE_Y}, TABLE_H, 2,
					   gui.getTheme().grid);
		GUI::drawVLine(Pos{TABLE_X + TIME_W + DATE_W, TABLE_Y}, TABLE_H, 2,
					   gui.getTheme().grid);

		timeLabel.draw();
		dateLabel.draw();
		linesLabel.draw();

		for (const auto& text : values) {
			text.draw();
		}

		GUI::drawOutline(
			Pos{TABLE_X, TABLE_Y + CELL_H * (selected + 1.0f - topCell)},
			WH{TABLE_W, CELL_H - 2}, 2, Theme::WHITE);

		selectedText.draw();
	} else {
		C2D_TargetClear(game.getBottom(), gui.getTheme().background);

		if (!games.empty()) {
			page.draw();
		}
		gui.draw();
	}
}

void SprintTimes::updateSelectedText() {
	selectedText.setText(
		sdscatfmt(sdsempty(), "%u/%u", selected + 1, games.size()));
	selectedText.align(Text::Align::HCENTER, Pos{},
					   {SCREEN_WIDTH, SCREEN_HEIGHT});
}

void SprintTimes::updateInfoText(const SavedGame& saved) {
	char date[60];
	saved.dateString(date, 60);
	page.setText(String::fromPrintf(infoFormat.s, saved.lines, saved.time,
									saved.pps, date));
}

// Thanks, C++11!
constexpr size_t SprintTimes::CELLS;
