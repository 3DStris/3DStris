#include <3dstris/gui/widgets/special/keybindbutton.hpp>
#include <3dstris/states/menu/mainmenu.hpp>
#include <3dstris/states/menu/settings/gameplay/keybindselect.hpp>

KeybindSelect::KeybindSelect()
	: State(),
	  title(game.translate("keybindselect.title")),

	  binds(game.getKeybinds().all()),

	  tip(gui, Pos{0, SCREEN_HEIGHT - 25}, WH{SCREEN_WIDTH, 25}, false),
	  tipText(game.translate("keybindselect.tip")),

	  save(gui.add<Button>(Pos(10, gui.getHeight() - 50), WH{75, 40},
						   game.translate("save"))),
	  reset(
		  gui.add<Button>(Pos((gui.getWidth() - 115) / 2, gui.getHeight() - 50),
						  WH{115, 40}, game.translate("reset"))),
	  cancel(gui.add<Button>(Pos(gui.getWidth() - 90, gui.getHeight() - 50),
							 WH{80, 40}, game.translate("cancel"))) {
	tipText.scale(tip.getWH().x, 0.5f);
	tipText.align(Text::Align::CENTER, tip.getPos(), tip.getWH());

	title.align(Text::Align::SCREEN_CENTER);

	constexpr float BUTTON_WIDTH = 80;
	constexpr float BUTTON_HEIGHT = 25;

	float x = 10;
	float y = 15;
	float textW = 0;
	for (const auto& bind : binds) {
		buttons.push_back(
			gui.add<KeybindButton>(Pos{x, y}, WH{BUTTON_WIDTH, BUTTON_HEIGHT},
								   bind.first, binds[bind.first]));
		Text label(
			game.translate(
				Keybinds::KEYBIND_TO_KEY[static_cast<size_t>(bind.first)]),
			Pos{x - 3, y - 3}, {0.4f, 0.4f});

		textW = std::max(label.getWH().x, textW);
		const float textH = label.getWH().y;

		label.setY(label.getY() - textH);
		labels.push_back(std::move(label));

		y += BUTTON_HEIGHT + 10 + textH;
		if (y + BUTTON_HEIGHT + 35 > gui.getHeight() ||
			y + BUTTON_HEIGHT + 35 + textH > gui.getHeight()) {
			y = 15;

			constexpr float X_OFFSET = BUTTON_WIDTH + 10;
			x += x + textW > x + X_OFFSET ? textW + 10 : X_OFFSET;
		}
	}
}

void KeybindSelect::update(const double dt) {
	gui.update(dt);

	if (save.pressed()) {
		for (const auto& button : buttons) {
			button.get().save();
		}
		game.getKeybinds().all() = binds;
		game.getKeybinds().save();

		game.popState();
	} else if (reset.pressed()) {
		for (const auto& button : buttons) {
			button.get().reset();
		}
	} else if (cancel.pressed() || hidKeysDown() & KEY_B) {
		game.popState();
	}
}

void KeybindSelect::draw(const bool bottom) {
	if (!bottom) {
		C2D_TargetClear(game.getTop(), gui.getTheme().background);

		tip.draw();
		tipText.draw();

		title.draw();
	} else {
		C2D_TargetClear(game.getBottom(), gui.getTheme().background);

		for (const auto& label : labels) {
			label.draw();
		}

		gui.draw();
	}
}
