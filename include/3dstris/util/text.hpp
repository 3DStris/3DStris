#pragma once

#include <sds.h>

#include <3dstris/util.hpp>
#include <3dstris/util/colorstextures.hpp>

class Text {
   public:
	enum class Align { CENTER, VCENTER, HCENTER, SCREEN_CENTER };

	explicit Text(sds text = sdsempty(), Pos pos = Pos{},
				  Vector2f scale = {1, 1}, Color color = WHITE);
	explicit Text(const char* __restrict text, Pos pos = Pos{},
				  Vector2f scale = {1, 1}, Color color = WHITE);

	~Text();
	Text(const Text& other) = delete;
	Text(Text&& other);
	Text& operator=(const Text& other) = delete;
	Text& operator=(Text&& other) = delete;

	void draw(float depth = 1) const;

	void align(Align mode, Pos cpos, WH cwh, bool bottom = false);
	void align(Align mode, bool bottom = false);

	void scale(float cx, float max);

	void setText(sds text);
	sds getText() const noexcept;

	void setX(float x) noexcept;
	float getX() const noexcept;

	void setY(float y) noexcept;
	float getY() const noexcept;

	void setPos(Pos pos) noexcept;

	WH getWH() const;

	void setColor(Color color);
	Color getColor() const noexcept;

	void setScaleX(float scale) noexcept;
	void setScaleY(float scale) noexcept;
	void setScale(Vector2f scale) noexcept;
	Vector2f getScale() const noexcept;

   private:
	Pos pos;
	Vector2f _scale;

	sds text = nullptr;

	Color color;

	C2D_Text textObject;
	C2D_TextBuf textBuffer;
};
