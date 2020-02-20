#include <3dstris/gui/u32inputfield.hpp>

U32InputField::U32InputField(GUI& _parent, const Pos _pos, const WH _wh,
							 const sds suffix)
	: Widget(_parent, _pos, _wh), suffix(suffix), value(0) {
	updateText();
}

U32InputField::U32InputField(GUI& _parent, const Pos _pos, const WH _wh,
							 const char* __restrict suffix)
	: U32InputField(_parent, _pos, _wh, sdsnew(suffix)) {}

U32InputField::~U32InputField() {
	sdsfree(suffix);
}

void U32InputField::draw() const {
	C2D_DrawRectSolid(pos.x, pos.y, 0, wh.x, wh.y, held ? FIELD_HELD : FIELD);
	text.draw();
}

void U32InputField::update(const touchPosition touch,
						   const touchPosition previous) {
	held = inside(touch.px, touch.py);

	if (inside(previous.px, previous.py) && hidKeysUp() & KEY_TOUCH) {
		SwkbdState swkbd;
		swkbdInit(&swkbd, SWKBD_TYPE_NUMPAD, 1, 6);
		swkbdSetValidation(&swkbd, SWKBD_NOTEMPTY_NOTBLANK, 0, 0);
		swkbdSetFeatures(&swkbd, SWKBD_FIXED_WIDTH);

		sds initialText = sdsfromlonglong(value);
		swkbdSetInitialText(&swkbd, initialText);

		char buf[6 + 1];
		swkbdInputText(&swkbd, buf, sizeof buf);

		sdsfree(initialText);

		char* end;
		errno = 0;
		const u32 tempValue = strtoul(buf, &end, 10);
		if (end[0] == '\0' && errno == 0) {
			value = tempValue;
			updateText();
		}
	}
}

bool U32InputField::inside(const float x, const float y) const {
	return x > pos.x && x < pos.x + wh.x &&  //
		   y > pos.y && y < pos.y + wh.y;
}

u32 U32InputField::getValue() const {
	return value;
}

void U32InputField::setValue(const u32 value) {
	this->value = value;
	updateText();
}

void U32InputField::updateText() {
	text.setText(sdscatfmt(sdsempty(), "%u%S", value, suffix));

	const float textScale = std::min(text.getWH().y / wh.y, 0.5f);
	text.setScale({textScale, textScale});

	text.align(Text::Align::VCENTER, pos, wh);
	text.setX(pos.x + 3);
}
