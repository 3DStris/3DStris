#include <3dstris/gui/togglebutton.hpp>

static sds getText(const sds text, const bool value) {
	return sdscatfmt(sdsnew(text), ": %s",
					 Game::get().translate(value ? "on" : "off"));
}

ToggleButton::ToggleButton(GUI& parent, const Pos pos, const WH wh,
						   const sds text, const bool defaultValue)
	: Button(parent, pos, wh, getText(text, defaultValue)),
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
		this->setText(getText(text, value));
	}
}

bool ToggleButton::getValue() {
	return value;
}
