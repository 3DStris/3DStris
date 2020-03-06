#pragma once

#include <3dstris/gui/widget.hpp>

class GUI;
class Panel : public Widget {
   public:
	Panel(GUI& parent, Pos pos, WH wh, bool outline = true, Color col = PANEL,
		  Color outlineCol = PANEL_OUTLINE);

	void draw() const override;
	void update(touchPosition, touchPosition) override;

   protected:
	static constexpr Color PANEL = C2D_Color32(35, 37, 55, 255);
	static constexpr Color PANEL_OUTLINE = C2D_Color32(37, 39, 58, 255);

   private:
	Color col;
	Color outlineCol;

	bool outline;
};
