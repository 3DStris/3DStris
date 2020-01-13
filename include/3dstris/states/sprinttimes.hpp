#pragma once

#include <3dstris/gui.hpp>
#include <3dstris/state.hpp>
#include <3dstris/util/text.hpp>

class SprintTimes : public State {
   public:
	SprintTimes();

	void update(const double dt) override;
	void draw(const bool bottom) override;

   private:
	static const u32 CELLS = 3;
	static const u32 CELL_H = 40;
	static const u32 TABLE_W = 300;
	static constexpr u32 TABLE_H = (CELLS + 1) * CELL_H;
	static constexpr u32 TABLE_X = (SCREEN_WIDTH - TABLE_W) / 2;
	static constexpr u32 TABLE_Y = (SCREEN_HEIGHT - TABLE_H) / 2;

	GUI gui;

	static constexpr u32 TIME_W = TABLE_W * 2 / 5;
	static constexpr u32 DATE_W = TABLE_W - TIME_W;

	Text timeLabel;
	Text dateLabel;
};
