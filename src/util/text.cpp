#include <3dstris/util/text.hpp>

Text::Text(const sds text, const Pos pos, const Vector2 scale,
		   const Color color)
	: pos(pos),
	  scale(scale),
	  color(color),
	  textBuffer(C2D_TextBufNew(sdslen(text))) {
	this->setText(text);
}

Text::Text(const char* text, const Pos pos, const Vector2 scale,
		   const Color color)
	: Text(sdsnew(text), pos, scale, color) {}

Text::~Text() {
	C2D_TextBufDelete(this->textBuffer);
	sdsfree(text);
}

Text::Text(const Text& other)
	: pos(other.pos),
	  scale(other.scale),
	  color(other.color),
	  textBuffer(C2D_TextBufNew(sdslen(other.text))) {
	this->setText(other.text);
}

Text& Text::operator=(const Text& other) {
	if (this != &other) {
		this->pos = other.pos;
		this->scale = other.scale;
		this->color = other.color;

		this->setText(other.text);
	}

	return *this;
}

void Text::align(const Align mode, const Pos cpos, const WH cwh,
				 const bool bottom) {
	auto wh = this->getWH();
	switch (mode) {
		case CENTER: {
			this->setPos(
				Pos{cpos.x + (cwh.x - wh.x) / 2, cpos.y + (cwh.y - wh.y) / 2});
			break;
		}
		case VCENTER: {
			this->setY(cpos.y + (cwh.y - wh.y) / 2);
			break;
		}
		case HCENTER: {
			this->setX(cpos.x + (cwh.x - wh.x) / 2);
			break;
		}
		case SCREEN_CENTER: {
			this->setPos(
				Pos{((!bottom ? SCREEN_WIDTH : BSCREEN_WIDTH) - wh.x) / 2,
					((!bottom ? SCREEN_HEIGHT : BSCREEN_HEIGHT) - wh.y) / 2});
			break;
		}
	}
}

void Text::align(const Align mode, const bool bottom) {
	align(mode, Pos{0, 0}, WH{0, 0}, bottom);
}

void Text::setText(const sds text) {
	sdsfree(this->text);
	this->text = text;

	C2D_TextBufClear(textBuffer);
	if (C2D_TextBufGetNumGlyphs(textBuffer) < sdslen(text)) {
		textBuffer = C2D_TextBufResize(textBuffer, sdslen(text));
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
	C2D_TextGetDimensions(&textObject, scale.x, scale.y, &width, &height);
	return {width, height};
}

void Text::setColor(Color color) {
	this->color = color;
}

Color Text::getColor() const noexcept {
	return color;
}

void Text::setScaleX(const float scale) noexcept {
	this->scale.x = scale;
}

void Text::setScaleY(const float scale) noexcept {
	this->scale.y = scale;
}

void Text::setScale(const Vector2 scale) noexcept {
	this->scale = scale;
}

Vector2 Text::getScale() const noexcept {
	return scale;
}

void Text::draw(const float depth) const {
	C2D_DrawText(&textObject, C2D_WithColor, pos.x, pos.y, depth, scale.x,
				 scale.y, color);
}
