#pragma once

#include <parallel_hashmap/phmap.h>

#include <3dstris/config/keybinds.hpp>
#include <3dstris/config/l10n.hpp>
#include <3dstris/gui/widgets/button.hpp>

class KeybindButton final : public Button {
   public:
	static const phmap::flat_hash_map<Keybinds::Key, const char*> KEY_TO_GLYPH;

	KeybindButton(GUI& parent, Pos pos, WH wh, Keybinds::Action action,
				  Keybinds::Key& toSet) noexcept;

	void update(touchPosition touch, touchPosition previous) override;

	void save() noexcept;
	void reset();

   private:
	void updateText();

	using Button::setText;

	const Keybinds::Action action;

	Keybinds::Key key;
	Keybinds::Key& toSet;
};
