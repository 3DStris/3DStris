#include <3dstris/util/text.hpp>

Text::Text(const sds text, const Color color)
	: pos({0, 0}), scale({1, 1}), color(color), textBuffer(C2D_TextBufNew(64)) {
	this->setText(text);
}

Text::Text(const char* text, const Color color) : Text(sdsnew(text), color) {}

Text::~Text() {
	C2D_TextBufDelete(this->textBuffer);
	sdsfree(text);
}

Text::Text(const Text& other)
	: pos(other.pos),
	  scale(other.scale),
	  color(other.color),
	  textBuffer(C2D_TextBufNew(64)) {
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

void Text::align(const Align mode, const Pos cpos, const Pos cwh,
				 const bool bottom) {
	auto wh = this->getWH();
	switch (mode) {
		case CENTER: {
			this->setPos({cpos.x + (cwh.x - wh.x) / 2.0f,
						  cpos.y + (cwh.y - wh.y) / 2.0f});
			break;
		}
		case VCENTER: {
			this->setY(cpos.y + (cwh.y - wh.y) / 2.0f);
			break;
		}
		case HCENTER: {
			this->setX(cpos.x + (cwh.x - wh.x) / 2.0f);
			break;
		}
		case SCREEN_CENTER: {
			this->setPos(
				{((!bottom ? SCREEN_WIDTH : BSCREEN_WIDTH) - wh.x) / 2.0f,
				 ((!bottom ? SCREEN_HEIGHT : BSCREEN_HEIGHT) - wh.y) / 2.0f});
			break;
		}
	}
}

void Text::align(const Align mode, const bool bottom) {
	align(mode, {0, 0}, {0, 0}, bottom);
}

void Text::setText(const sds text) {
	sdsfree(this->text);
	this->text = text;

	C2D_TextBufClear(this->textBuffer);

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

void Text::setPos(Vector2 pos) noexcept {
	this->pos = pos;
}

Vector2 Text::getWH() const {
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

void Text::setScaleX(float scale) noexcept {
	this->scale.x = scale;
}

void Text::setScaleY(float scale) noexcept {
	this->scale.y = scale;
}

void Text::setScale(Vector2 scale) noexcept {
	this->scale = scale;
}

Vector2 Text::getScale() const noexcept {
	return scale;
}

void Text::draw() const {
	C2D_DrawText(&textObject, C2D_WithColor, pos.x, pos.y, 0.5f, scale.x,
				 scale.y, color);
}
