#include <3dstris/gui.hpp>
#include <3dstris/gui/doubleinputfield.hpp>

DoubleInputField::DoubleInputField(GUI& _parent, const Vector2 _pos,
								   const Vector2 _wh, const sds suffix)
	: Widget(_parent, _pos, _wh), suffix(suffix), value(0.) {
	updateText();
}

DoubleInputField::DoubleInputField(GUI& _parent, const Vector2 _pos,
								   const Vector2 _wh, const char* suffix)
	: DoubleInputField(_parent, _pos, _wh, sdsnew(suffix)) {}

DoubleInputField::~DoubleInputField() {
	sdsfree(suffix);
}

void DoubleInputField::draw() const {
	C2D_DrawRectSolid(pos.x, pos.y, 0, wh.x, wh.y, held ? FIELD_HELD : FIELD);
	text.draw();
}

void DoubleInputField::update(const touchPosition touch,
							  const touchPosition previous) {
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

bool DoubleInputField::inside(const float posX, const float posY) const {
	return posX > pos.x && posX < pos.x + wh.x &&  //
		   posY > pos.y && posY < pos.y + wh.y;
}

double DoubleInputField::getValue() const {
	return value;
}

void DoubleInputField::setValue(const double v) {
	value = v;
	updateText();
}

void DoubleInputField::updateText() {
	this->text.setText(sdscatprintf(sdsempty(), "%.9g%s", value, suffix));

	auto textScale = std::min(this->text.getWH().y / wh.y, 0.5f);
	this->text.setScale({textScale, textScale});

	this->text.align(Text::Align::VCENTER, pos, wh);
	this->text.setX(pos.x + 3);
}
