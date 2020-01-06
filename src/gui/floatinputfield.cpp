#include <3dstris/gui.hpp>
#include <3dstris/gui/floatinputfield.hpp>

FloatInputField::FloatInputField(GUI& parent, float x, float y, float w,
								 float h, const sds suffix)
	: Widget(parent), suffix(suffix), x(x), y(y), w(w), h(h), value(0.0f) {
	updateText();
}

FloatInputField::FloatInputField(GUI& parent, float x, float y, float w,
								 float h, const char* suffix)
	: FloatInputField(parent, x, y, w, h, sdsnew(suffix)) {}

FloatInputField::~FloatInputField() {
	sdsfree(suffix);
}

void FloatInputField::draw() const {
	C2D_DrawRectSolid(x, y - h / 2.0f, 0, w, h, held ? FIELD_HELD : FIELD);
	text.draw();
}

void FloatInputField::update(touchPosition touch, touchPosition previous) {
	held = inside(touch.px, touch.py);

	if (inside(previous.px, previous.py) && hidKeysUp() & KEY_TOUCH) {
		SwkbdState swkbd;

		sds initialText = sdscatprintf(sdsempty(), "%.4f", value);

		char buf[5];
		swkbdInit(&swkbd, SWKBD_TYPE_NUMPAD, 1, 4);
		swkbdSetValidation(&swkbd, SWKBD_NOTEMPTY_NOTBLANK, 0, 0);
		swkbdSetFeatures(&swkbd, SWKBD_FIXED_WIDTH);
		swkbdSetNumpadKeys(&swkbd, '.', 0);
		swkbdSetInitialText(&swkbd, initialText);
		swkbdInputText(&swkbd, buf, sizeof(buf));

		sdsfree(initialText);

		float tempValue = std::atof(buf);
		if (tempValue != 0.f) {
			value = tempValue;
			updateText();
		}
	}
}

bool FloatInputField::inside(float posX, float posY) const {
	return posX > x && posX < x + w &&  //
		   posY > y - h / 2 && posY < y + h / 2;
}

float FloatInputField::getValue() const {
	return value;
}

void FloatInputField::setValue(float v) {
	value = v;
	updateText();
}

void FloatInputField::updateText() {
	this->text.setText(sdscatprintf(sdsempty(), "%.2f%s", value, suffix));

	auto textScale = std::min(this->text.getWH().y / h, 0.5f);
	this->text.setScale({textScale, textScale});

	this->text.setPos({x + 3, y - (h / text.getWH().y) * 4});
}
