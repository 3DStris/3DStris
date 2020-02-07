#pragma once

#include <sds.h>
#include <3dstris/colors.hpp>
#include <3dstris/util.hpp>

class Text {
   public:
	enum Align { CENTER, VCENTER, HCENTER, SCREEN_CENTER };

	Text(const sds text = sdsempty(), const Pos pos = Pos{},
		 const Vector2 scale = {1, 1}, const Color color = WHITE);
	Text(const char* text, const Pos pos = Pos{}, const Vector2 scale = {1, 1},
		 const Color color = WHITE);
	~Text();

	Text(const Text& other);
	Text& operator=(const Text& other);

	void align(const Align mode, const Vector2 cpos, const Vector2 cwh,
			   const bool bottom = false);
	void align(const Align mode, const bool bottom = false);

	void setText(sds text);
	sds getText() const noexcept;

	void setX(const float x) noexcept;
	float getX() const noexcept;

	void setY(const float y) noexcept;
	float getY() const noexcept;

	void setPos(const Pos pos) noexcept;

	WH getWH() const;

	void setColor(const Color color);
	Color getColor() const noexcept;

	void setScaleX(const float scale) noexcept;
	void setScaleY(const float scale) noexcept;
	void setScale(const Vector2 scale) noexcept;
	Vector2 getScale() const noexcept;

	void draw(const float depth = 1) const;

   private:
	Pos pos;
	Vector2 scale;
	sds text = nullptr;
	Color color;
	C2D_Text textObject;
	C2D_TextBuf textBuffer;
};
