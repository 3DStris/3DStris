#include <3dstris/util/text.hpp>

Text::Text(const char* text, Color color)
	: pos({0, 0}), scale({1, 1}), color(color), textBuffer(C2D_TextBufNew(64)) {
	this->setText(text);
}

Text::~Text() {
	C2D_TextBufDelete(this->textBuffer);
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

void Text::setText(const char* text) {
	this->text = text;

	C2D_TextBufClear(this->textBuffer);

	C2D_TextParse(&textObject, textBuffer, this->text);
	C2D_TextOptimize(&textObject);
}

const char* Text::getText() {
	return text;
}

void Text::setX(float x) {
	pos.x = x;
}

float Text::getX() const {
	return pos.x;
}

void Text::setY(float y) {
	pos.y = y;
}

float Text::getY() const {
	return pos.y;
}

void Text::setPos(float x, float y) {
	pos.x = x;
	pos.y = y;
}

void Text::setPos(Vector2 vector) {
	pos = vector;
}

Vector2 Text::getWH() const {
	float width, height;
	C2D_TextGetDimensions(&textObject, scale.x, scale.y, &width, &height);
	return {width, height};
}

void Text::setColor(Color color) {
	this->color = color;
}

Color Text::getColor() const {
	return color;
}

void Text::setScaleX(float scale) {
	this->scale.x = scale;
}

void Text::setScaleY(float scale) {
	this->scale.y = scale;
}

void Text::setScale(Vector2 scale) {
	this->scale = scale;
}

Vector2 Text::getScale() const {
	return scale;
}

void Text::draw() const {
	C2D_DrawText(&textObject, C2D_WithColor, pos.x, pos.y, 0.5f, scale.x,
				 scale.y, color);
}
