#pragma once

#include <3dstris/gui.hpp>
#include <3dstris/gui/widgets/panel.hpp>
#include <3dstris/state.hpp>

class SprintTimes final : public State {
   public:
	SprintTimes();

	void update(double dt) override;
	void draw(bool bottom) const noexcept override;

	void genValues();

   private:
	static constexpr size_t CELLS = 3;

	static constexpr u16 CELL_H = 40;
	static constexpr u16 TABLE_W = 350;
	static constexpr u16 TABLE_H = (CELLS + 1) * CELL_H;
	static constexpr u16 TABLE_X = (SCREEN_WIDTH - TABLE_W) / 2;
	static constexpr u16 TABLE_Y = (SCREEN_HEIGHT - TABLE_H) / 2;

	void updateInfoText(const SavedGame& game);
	void updateSelectedText();

	const String infoFormat;

	GUI gui;
	Panel panel;
	Button& back;

	static constexpr u16 TIME_W = TABLE_W * 2 / 6;
	static constexpr u16 DATE_W = (TABLE_W - TIME_W) * 2 / 3;
	static constexpr u16 LINES_W = TABLE_W - TIME_W - DATE_W;

	Text timeLabel;
	Text dateLabel;
	Text linesLabel;

	u32 topCell = 0;
	u32 selected = 0;

	std::vector<Text> values;
	Games::SavedGames games;

	Text title;
	Text noGames;
	Text page;
	Text selectedText;
};
