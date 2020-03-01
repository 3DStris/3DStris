#include <3dstris/gui/keybindbutton.hpp>
#include <3dstris/states/menu/keybindselect.hpp>
#include <3dstris/states/menu/mainmenu.hpp>

KeybindSelect::KeybindSelect()
	: State(),
	  selectText(game.translate("keybindselect.title")),

	  binds(game.getKeybinds().all()),

	  tip(gui, {0, SCREEN_HEIGHT - 25}, {SCREEN_WIDTH, 25}, false),
	  tipText(game.translate("keybindselect.tip")),

	  saveButton(gui.add<Button>(Pos{10, BSCREEN_HEIGHT - 50}, WH{75, 40},
								 game.translate("save"))),
	  resetButton(
		  gui.add<Button>(Pos{(BSCREEN_WIDTH - 115) / 2, BSCREEN_HEIGHT - 50},
						  WH{115, 40}, game.translate("reset"))),
	  cancelButton(gui.add<Button>(Pos{BSCREEN_WIDTH - 90, BSCREEN_HEIGHT - 50},
								   WH{80, 40}, game.translate("cancel"))) {
	tipText.scale(tip.getWH().x, 0.5f);
	tipText.align(Text::Align::CENTER, tip.getPos(), tip.getWH());

	selectText.align(Text::Align::SCREEN_CENTER);

	constexpr float BUTTON_WIDTH = 80;
	constexpr float BUTTON_HEIGHT = 25;

	float x = 10;
	float y = 15;
	float textW = 0;
	for (const auto& bind : binds) {
		buttons.push_back(
			gui.add<KeybindButton>(Pos{x, y}, WH{BUTTON_WIDTH, BUTTON_HEIGHT},
								   bind.first, binds[bind.first]));
		Text label(game.translate(Keybinds::KEYBIND_TO_KEY[bind.first]),
				   Pos{x - 3, y - 3}, {0.4f, 0.4f});

		textW = std::max(label.getWH().x, textW);
		const float textH = label.getWH().y;

		label.setY(label.getY() - textH);
		labels.push_back(std::move(label));

		y += BUTTON_HEIGHT + 10 + textH;
		if (y + BUTTON_HEIGHT + 35 > SCREEN_HEIGHT ||
			y + BUTTON_HEIGHT + 35 + textH > SCREEN_HEIGHT) {
			y = 15;

			constexpr float X_OFFSET = BUTTON_WIDTH + 10;
			x += x + textW > x + X_OFFSET ? textW + 10 : X_OFFSET;
		}
	}
}

void KeybindSelect::update(const double dt) {
	gui.update(dt);

	if (saveButton.pressed()) {
		for (const auto& button : buttons) {
			button.get().save();
		}
		game.getKeybinds().all() = binds;
		game.getKeybinds().save();

		game.setState(make_unique<MainMenu>());
		return;
	}

	if (resetButton.pressed()) {
		for (const auto& button : buttons) {
			button.get().reset();
		}
	}

	if (cancelButton.pressed()) {
		game.popState();
	}
}

void KeybindSelect::draw(const bool bottom) {
	if (!bottom) {
		C2D_TargetClear(game.getTop(), BACKGROUND);

		tip.draw();
		tipText.draw();

		selectText.draw();
	} else {
		C2D_TargetClear(game.getBottom(), BACKGROUND);

		for (const auto& label : labels) {
			label.draw();
		}

		gui.draw();
	}
}
