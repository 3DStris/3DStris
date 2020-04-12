#include <3dstris/game.hpp>
#include <3dstris/gui/widgets/togglebutton.hpp>

static String getText(const String& text, const bool value) {
	return String::fromFmt(
		"%S: %S", text.s,
		Game::get().translate(value ? StringView("on") : StringView("off")).s);
}

ToggleButton::ToggleButton(GUI& _parent, const Pos _pos, const WH _wh,
						   String&& text, const bool defaultValue) noexcept
	: Button(_parent, _pos, _wh, getText(text, defaultValue)),
	  text(text),
	  value(defaultValue) {}

void ToggleButton::update(const touchPosition touch,
						  const touchPosition previous) noexcept {
	Button::update(touch, previous);

	if (pressed()) {
		value = !value;
		setText(getText(text, value));
	}
}

bool ToggleButton::getValue() const noexcept {
	return value;
}
