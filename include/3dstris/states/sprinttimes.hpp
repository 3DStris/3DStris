#pragma once

#include <3dstris/gui.hpp>
#include <3dstris/gui/panel.hpp>
#include <3dstris/state.hpp>
#include <3dstris/util/text.hpp>

class SprintTimes : public State {
   public:
	SprintTimes();
	~SprintTimes();

	void update(const double dt) override;
	void draw(const bool bottom) override;

	void genValues();

   private:
	static const u8 CELLS = 3;
	static const u16 CELL_H = 40;
	static const u16 TABLE_W = 300;
	static const u16 TABLE_H = (CELLS + 1) * CELL_H;
	static const u16 TABLE_X = (SCREEN_WIDTH - TABLE_W) / 2;
	static const u16 TABLE_Y = (SCREEN_HEIGHT - TABLE_H) / 2;

	void updateInfoText(const SavedGame& game);
	void updateSelectedText();

	const sds infoFormat;

	GUI gui;
	Panel panel;
	Button& backButton;

	static const u16 TIME_W = TABLE_W * 2 / 5;
	static const u16 DATE_W = TABLE_W - TIME_W;

	Text timeLabel;
	Text dateLabel;

	u32 topCell = 0;
	u32 selected = 0;

	std::vector<Text> values;
	SavedGames games;

	Text titleText;
	Text noGamesText;
	Text infoText;
	Text selectedText;
};
