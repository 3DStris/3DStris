#pragma once

#include <sds.h>

#include <3dstris/game.hpp>
#include <3dstris/util/colorstextures.hpp>
#include <3dstris/util/math.hpp>
#include <3dstris/util/string.hpp>

class Text {
   public:
	enum class Align { CENTER, VCENTER, HCENTER, SCREEN_CENTER };

	explicit Text(String&& text = String::empty(), Pos pos = Pos{},
				  Vector2f scale = {1, 1},
				  const Color& color = Game::get().getTheme().text) noexcept;

	void draw(float depth = 1) const noexcept;

	void align(Align mode, Pos cpos, WH cwh, bool bottom = false) noexcept;
	void align(Align mode, bool bottom = false) noexcept;

	void scale(float cw, float max) noexcept;

	void setText(String&& text) noexcept;
	const String& getText() const noexcept;

	void setX(float x) noexcept;
	float getX() const noexcept;

	void setY(float y) noexcept;
	float getY() const noexcept;

	void setPos(Pos pos) noexcept;

	WH getWH() const noexcept;

	Color getColor() const noexcept;

	void setScaleX(float scale) noexcept;
	void setScaleY(float scale) noexcept;
	void setScale(Vector2f scale) noexcept;
	Vector2f getScale() const noexcept;

   private:
	Pos pos;
	Vector2f _scale;

	String text;
	C2D_TextBuf textBuffer;
	C2D_Text textObject;

	const Color& color;
};
