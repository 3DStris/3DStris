#include <3dstris/util/text.hpp>

Text::Text(sds text, const Pos pos, const Vector2f scale, const Color color)
	: pos(pos),
	  _scale(scale),
	  color(color),
	  textBuffer(C2D_TextBufNew(sdslen(text))) {
	setText(text);
}
Text::Text(const char* __restrict text, const Pos pos, const Vector2f scale,
		   const Color color)
	: Text(sdsnew(text), pos, scale, color) {}

Text::~Text() {
	C2D_TextBufDelete(textBuffer);
	sdsfree(text);
}
Text::Text(Text&& other)
	: pos(other.pos),
	  _scale(other._scale),
	  text(other.text),
	  color(other.color),
	  textObject(other.textObject),
	  textBuffer(other.textBuffer) {
	other.textBuffer = nullptr;
	other.text = nullptr;
}

void Text::draw(const float depth) const {
	C2D_DrawText(&textObject, C2D_WithColor, pos.x, pos.y, depth, _scale.x,
				 _scale.y, color);
}

void Text::align(const Align mode, const Pos cpos, const WH cwh,
				 const bool bottom) {
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
void Text::align(const Align mode, const bool bottom) {
	align(mode, Pos{}, WH{}, bottom);
}

void Text::scale(const float cx, const float max) {
	setScale({1, 1});

	const float linesScale = std::min((cx - 10) / getWH().x, max);
	setScale({linesScale, linesScale});
}

void Text::setText(sds text) {
	sdsfree(this->text);
	this->text = text;

	C2D_TextBufClear(textBuffer);

	const size_t textLen = sdslen(text);
	if (C2D_TextBufGetNumGlyphs(textBuffer) < textLen) {
		textBuffer = C2D_TextBufResize(textBuffer, textLen);
	}

	C2D_TextParse(&textObject, textBuffer, this->text);
	C2D_TextOptimize(&textObject);
}

sds Text::getText() const noexcept {
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

WH Text::getWH() const {
	float width, height;
	C2D_TextGetDimensions(&textObject, _scale.x, _scale.y, &width, &height);
	return {width, height};
}

void Text::setColor(const Color color) {
	this->color = color;
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
