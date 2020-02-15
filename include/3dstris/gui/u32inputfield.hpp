#pragma once

#include <3dstris/gui/widget.hpp>
#include <3dstris/util/text.hpp>

class GUI;
class U32InputField : public Widget {
   public:
	U32InputField(GUI& parent, const Pos pos, const WH wh,
				  const sds suffix = sdsempty());
	U32InputField(GUI& parent, const Pos pos, const WH wh, const char* suffix);
	~U32InputField() override;

	void draw() const override;
	void update(const touchPosition touch, const touchPosition) override;

	bool inside(const float x, const float y) const;

	u32 getValue() const;
	void setValue(const u32 value);

   private:
	static constexpr Color FIELD = C2D_Color32(94, 94, 94, 255);
	static constexpr Color FIELD_HELD = C2D_Color32(75, 75, 75, 255);

	void updateText();

	Text text;
	sds suffix;

	u32 value;

	bool held;
};
