#include <3dstris/gui.hpp>
#include <3dstris/gui/floatinputfield.hpp>

FloatInputField::FloatInputField(GUI& parent, float x, float y, float w,
								 float h)
	: Widget(parent), x(x), y(y), w(w), h(h), value(0.0f) {
	updateText();
}

void FloatInputField::draw() const {
	C2D_DrawRectSolid(x, y - h / 2.0f, 0, w, h, parent.borderCol);
	text.draw();
}

void FloatInputField::update(touchPosition touch, touchPosition) {
	if (hidKeysDown() & KEY_TOUCH && inside(touch.px, touch.py)) {
		SwkbdState swkbd;

		char buf[5];
		swkbdInit(&swkbd, SWKBD_TYPE_NUMPAD, 1, 4);
		swkbdSetValidation(&swkbd, SWKBD_NOTEMPTY_NOTBLANK, 0, 0);
		swkbdSetFeatures(&swkbd, SWKBD_FIXED_WIDTH);
		swkbdSetNumpadKeys(&swkbd, '.', 0);
		swkbdInputText(&swkbd, buf, sizeof(buf));

		float tempValue = std::atof(buf);
		if (tempValue != 0.f) {
			value = tempValue;
			updateText();
		}
	}
}

bool FloatInputField::inside(float posX, float posY) const {
	return posX > x && posX < x + w &&  //
		   posY > y && posY < y + h;
}

float FloatInputField::getValue() const {
	return value;
}

void FloatInputField::setValue(float v) {
	value = v;
	updateText();
}

void FloatInputField::updateText() {
	this->text.setText(sdscatprintf(sdsempty(), "%.2f", value));

	auto textScale = std::min(this->text.getWH().y / h, 0.5f);
	this->text.setScale({textScale, textScale});

	this->text.setPos({x + 3, y - (h / text.getWH().y) * 4});
}
