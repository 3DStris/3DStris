#pragma once

#include <3dstris/gui/widget.hpp>
#include <3dstris/util/text.hpp>

class GUI;
class DoubleInputField : public Widget {
   public:
	DoubleInputField(GUI& parent, const Pos pos, const WH wh,
					 const sds suffix = sdsempty());
	DoubleInputField(GUI& parent, const Pos pos, const WH wh,
					 const char* suffix);
	~DoubleInputField() override;

	void draw() const override;
	void update(touchPosition touch, touchPosition) override;

	bool inside(const float posX, const float posY) const;

	double getValue() const;
	void setValue(const double v);

   private:
	static constexpr Color FIELD = C2D_Color32(94, 94, 94, 255);
	static constexpr Color FIELD_HELD = C2D_Color32(75, 75, 75, 255);

	void updateText();

	Text text;
	sds suffix;

	double value;

	bool held;
};
