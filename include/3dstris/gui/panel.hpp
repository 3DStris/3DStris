#pragma once

#include <3dstris/gui/widget.hpp>
#include <3dstris/util/text.hpp>

class GUI;
class Panel : public Widget {
   public:
	Panel(GUI& parent, const Pos pos, const WH wh, bool outline = true,
		  const Color col = PANEL, const Color outlineCol = PANEL_OUTLINE);

	void draw() const override;
	void update(const touchPosition, const touchPosition) override;

   private:
	static constexpr Color PANEL = C2D_Color32(60, 60, 60, 255);
	static constexpr Color PANEL_OUTLINE = C2D_Color32(88, 88, 88, 255);

	Color col;
	Color outlineCol;

	bool outline;
};
