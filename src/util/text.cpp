#include <3dstris/util/draw.hpp>
#include <3dstris/util/text.hpp>

Text::Text(String&& text, const Pos pos, const Vector2f scale,
		   const Color& color) noexcept
	: pos(pos),
	  _scale(scale),
	  textBuffer(C2D_TextBufNew(sdslen(text))),
	  color(color) {
	setText(std::forward<String>(text));
}

void Text::draw(const float depth) const noexcept {
	C2D_DrawText(&textObject, C2D_WithColor, pos.x, pos.y, depth, _scale.x,
				 _scale.y, color);
}

void Text::align(const Align mode, const Pos cpos, const WH cwh,
				 const bool bottom) noexcept {
	const WH wh = getWH();
	switch (mode) {
		case Align::CENTER: {
			setPos(
				Pos{cpos.x + (cwh.x - wh.x) / 2, cpos.y + (cwh.y - wh.y) / 2});
			break;
		}
		case Align::VCENTER: {
			setY(cpos.y + (cwh.y - wh.y) / 2);
			break;
		}
		case Align::HCENTER: {
			setX(cpos.x + (cwh.x - wh.x) / 2);
			break;
		}
		case Align::SCREEN_CENTER: {
			setPos(
				Pos{((!bottom ? SCREEN_WIDTH : BSCREEN_WIDTH) - wh.x) / 2,
					((!bottom ? SCREEN_HEIGHT : BSCREEN_HEIGHT) - wh.y) / 2});
			break;
		}
	}
}
void Text::align(const Align mode, const bool bottom) noexcept {
	align(mode, Pos{}, WH{}, bottom);
}

void Text::scale(const float cw, const float max) noexcept {
	setScale({1, 1});

	const float scale = std::min((cw - 10) / getWH().x, max);
	setScale({scale, scale});
}

void Text::setText(String&& text) noexcept {
	this->text = std::forward<String>(text);

	C2D_TextBufClear(textBuffer);

	const size_t textLen = sdslen(this->text);
	if (C2D_TextBufGetNumGlyphs(textBuffer) < textLen) {
		textBuffer = C2D_TextBufResize(textBuffer, textLen);
	}

	C2D_TextParse(&textObject, textBuffer, this->text);
	C2D_TextOptimize(&textObject);
}

const String& Text::getText() const noexcept {
	return text;
}

void Text::setX(const float x) noexcept {
	pos.x = x;
}
float Text::getX() const noexcept {
	return pos.x;
}

void Text::setY(const float y) noexcept {
	pos.y = y;
}
float Text::getY() const noexcept {
	return pos.y;
}

void Text::setPos(const Pos pos) noexcept {
	this->pos = pos;
}

WH Text::getWH() const noexcept {
	WH wh;
	C2D_TextGetDimensions(&textObject, _scale.x, _scale.y, &wh.x, &wh.y);
	return wh;
}

Color Text::getColor() const noexcept {
	return color;
}

void Text::setScaleX(const float scale) noexcept {
	_scale.x = scale;
}
void Text::setScaleY(const float scale) noexcept {
	_scale.y = scale;
}
void Text::setScale(const Vector2f scale) noexcept {
	_scale = scale;
}
Vector2f Text::getScale() const noexcept {
	return _scale;
}
