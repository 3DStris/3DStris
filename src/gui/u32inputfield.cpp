#include <3dstris/gui/u32inputfield.hpp>

U32InputField::U32InputField(GUI& _parent, const Vector2 _pos,
							 const Vector2 _wh, const sds suffix)
	: Widget(_parent, _pos, _wh), suffix(suffix), value(0) {
	updateText();
}

U32InputField::U32InputField(GUI& _parent, const Vector2 _pos,
							 const Vector2 _wh, const char* suffix)
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

		sds initialText = sdscatfmt(sdsempty(), "%u", value);

		char buf[7];
		swkbdInit(&swkbd, SWKBD_TYPE_NUMPAD, 1, 6);
		swkbdSetValidation(&swkbd, SWKBD_NOTEMPTY_NOTBLANK, 0, 0);
		swkbdSetFeatures(&swkbd, SWKBD_FIXED_WIDTH);
		swkbdSetInitialText(&swkbd, initialText);
		swkbdInputText(&swkbd, buf, sizeof(buf));

		sdsfree(initialText);

		char* end;
		errno = 0;
		u32 tempValue = strtoul(buf, &end, 10);
		if (end[0] == '\0' && errno == 0) {
			value = tempValue;
			updateText();
		}
	}
}

bool U32InputField::inside(const float posX, const float posY) const {
	return posX > pos.x && posX < pos.x + wh.x &&  //
		   posY > pos.y && posY < pos.y + wh.y;
}

u32 U32InputField::getValue() const {
	return value;
}

void U32InputField::setValue(const u32 v) {
	value = v;
	updateText();
}

void U32InputField::updateText() {
	this->text.setText(sdscatfmt(sdsempty(), "%u%S", value, suffix));

	auto textScale = std::min(this->text.getWH().y / wh.y, 0.5f);
	this->text.setScale({textScale, textScale});

	this->text.align(Text::Align::VCENTER, pos, wh);
	this->text.setX(pos.x + 3);
}
