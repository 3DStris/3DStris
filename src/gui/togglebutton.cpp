#include <3dstris/game.hpp>
#include <3dstris/gui/togglebutton.hpp>

static sds getText(const sds text, const bool value) {
	return sdscatfmt(sdsnew(text), ": %s",
					 Game::get().translate(value ? "on" : "off"));
}

ToggleButton::ToggleButton(GUI& _parent, const Pos _pos, const WH _wh,
						   const sds text, const bool defaultValue)
	: Button(_parent, _pos, _wh, getText(text, defaultValue)),
	  text(text),
	  value(defaultValue) {}

ToggleButton::~ToggleButton() {
	sdsfree(text);
}

void ToggleButton::update(const touchPosition touch,
						  const touchPosition previous) {
	Button::update(touch, previous);

	if (pressed()) {
		value = !value;
		setText(getText(text, value));
	}
}

bool ToggleButton::getValue() {
	return value;
}
