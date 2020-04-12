#pragma once

#include <sds.h>

#include <3dstris/game.hpp>
#include <3dstris/util/colorstextures.hpp>
#include <3dstris/util/math.hpp>
#include <3dstris/util/string.hpp>

class Text {
   public:
	enum class Align { CENTER, VCENTER, HCENTER, SCREEN_CENTER };

	explicit Text()
		: _scale(1, 1),
		  textBuffer(C2D_TextBufNew(1)),
		  color(Game::get().getTheme().text) {
		setText(String::empty());
	}
	template <typename T>
	explicit Text(T&& text, Pos pos = Pos{}, Vector2f scale = {1, 1},
				  const Color& color = Game::get().getTheme().text) noexcept
		: pos(pos),
		  _scale(scale),
		  textBuffer(C2D_TextBufNew(text.length())),
		  color(color) {
		setText(text);
	}

	void draw(float depth = 1) const noexcept;

	void align(Align mode, Pos cpos, WH cwh, bool bottom = false) noexcept;
	void align(Align mode, bool bottom = false) noexcept;

	void scale(float cw, float max) noexcept;

	template <typename T>
	void setText(T&& text) noexcept {
		this->text = String(text);

		C2D_TextBufClear(textBuffer);

		const size_t textLen = this->text.length();
		if (C2D_TextBufGetNumGlyphs(textBuffer) < textLen) {
			textBuffer = C2D_TextBufResize(textBuffer, textLen);
		}

		C2D_TextParse(&textObject, textBuffer, this->text);
		C2D_TextOptimize(&textObject);
	}
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
