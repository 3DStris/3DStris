#include <3dstris/gui.hpp>
#include <3dstris/gui/doubleinputfield.hpp>

DoubleInputField::DoubleInputField(GUI& parent, float x, float y, float w,
								 float h, const sds suffix)
	: Widget(parent), suffix(suffix), x(x), y(y), w(w), h(h), value(0.) {
	updateText();
}

DoubleInputField::DoubleInputField(GUI& parent, float x, float y, float w,
								 float h, const char* suffix)
	: DoubleInputField(parent, x, y, w, h, sdsnew(suffix)) {}

DoubleInputField::~DoubleInputField() {
	sdsfree(suffix);
}

void DoubleInputField::draw() const {
	C2D_DrawRectSolid(x, y - h / 2.0f, 0, w, h, held ? FIELD_HELD : FIELD);
	text.draw();
}

void DoubleInputField::update(touchPosition touch, touchPosition previous) {
	held = inside(touch.px, touch.py);

	if (inside(previous.px, previous.py) && hidKeysUp() & KEY_TOUCH) {
		SwkbdState swkbd;

		sds initialText = sdscatprintf(sdsempty(), "%.9g", value);

		char buf[12];
		swkbdInit(&swkbd, SWKBD_TYPE_NUMPAD, 1, 11);
		swkbdSetValidation(&swkbd, SWKBD_NOTEMPTY_NOTBLANK, 0, 0);
		swkbdSetFeatures(&swkbd, SWKBD_FIXED_WIDTH);
		swkbdSetNumpadKeys(&swkbd, '.', 'e');
		swkbdSetInitialText(&swkbd, initialText);
		swkbdInputText(&swkbd, buf, sizeof(buf));

		sdsfree(initialText);

		char* end;
		errno = 0;
		double tempValue = strtod(buf, &end);
		if (end[0] == '\0' && errno == 0) {
			value = tempValue;
			updateText();
		}
	}
}

bool DoubleInputField::inside(float posX, float posY) const {
	return posX > x && posX < x + w &&  //
		   posY > y - h / 2 && posY < y + h / 2;
}

double DoubleInputField::getValue() const {
	return value;
}

void DoubleInputField::setValue(double v) {
	value = v;
	updateText();
}

void DoubleInputField::updateText() {
	this->text.setText(sdscatprintf(sdsempty(), "%.9g%s", value, suffix));

	auto textScale = std::min(this->text.getWH().y / h, 0.5f);
	this->text.setScale({textScale, textScale});

	this->text.setPos({x + 3, y - text.getWH().y / 2.0f});
}
