#include <3dstris/game.hpp>
#include <3dstris/gui/keybindbutton.hpp>

#define ALL(direction)           \
	case KEY_D##direction:       \
	case KEY_CPAD_##direction:   \
	case KEY_CSTICK_##direction: \
		key = KEY_##direction;   \
		break;

#define KEY(key, code) \
	{ KEY_##key, code }

const phmap::flat_hash_map<Keybinds::Key, const char*>
	KeybindButton::KEY_TO_GLYPH{
		KEY(A, "\uE000"),	 KEY(B, "\uE001"),
		KEY(X, "\uE002"),	 KEY(Y, "\uE003"),
		KEY(L, "\uE004"),	 KEY(R, "\uE005"),
		KEY(UP, "\uE079"),	KEY(DOWN, "\uE07A"),
		KEY(LEFT, "\uE07B"),  KEY(RIGHT, "\uE07C"),
		KEY(ZL, "\uE054"),	KEY(ZR, "\uE055"),
		KEY(TOUCH, "\uE01D"), {KEY_A | KEY_X, "\uE000/\uE001"}};

KeybindButton::KeybindButton(GUI& _parent, const Pos _pos, const WH _wh,
							 const Keybinds::Action action,
							 Keybinds::Key& toSet)
	: Button(_parent, _pos, _wh, sdsempty()),
	  action(action),
	  key(toSet),
	  toSet(toSet) {
	updateText();
}

void KeybindButton::draw() const {
	Button::draw();
}

void KeybindButton::update(const touchPosition touch,
						   const touchPosition previous) {
	Button::update(touch, previous);

	if (pressed()) {
		key = hidKeysDown();
		do {
			hidScanInput();
			Keybinds::Key kDown = hidKeysDown();
			if (kDown & KEY_START) {
				return;
			} else if (kDown & KEY_SELECT) {
				reset();
				return;
			}
			key = kDown;

			svcSleepThread(500000);  // 0.5ms
		} while (key == 0);

		switch (key) {
			ALL(RIGHT)
			ALL(LEFT)
			ALL(UP)
			ALL(DOWN)
		}

		updateText();
	}
}

void KeybindButton::save() {
	if (key != 0) {
		toSet = key;
	}
}

void KeybindButton::reset() {
	key = Keybinds::DEFAULT_BINDS.at(action);
	updateText();
}

void KeybindButton::updateText() {
	try {
		setText(sdsnew(KEY_TO_GLYPH.at(key)));
	} catch (...) {
		setText(sdsnew("?"));
	}
}
