#pragma once

#include <parallel_hashmap/phmap.h>
#include <3dstris/config/keybinds.hpp>
#include <3dstris/config/l10n.hpp>
#include <3dstris/gui/button.hpp>

class KeybindButton : public Button {
   public:
	const static phmap::flat_hash_map<Keybinds::Key, const char*> KEY_TO_GLYPH;

	KeybindButton(GUI& parent, const Pos pos, const WH wh,
				  const Keybinds::Action action, Keybinds::Key& toSet);

	void draw() const override;
	void update(const touchPosition touch,
				const touchPosition previous) override;

	void save();
	void reset();

   private:
	void updateText();

	using Button::setText;

	const Keybinds::Action action;

	Keybinds::Key key;
	Keybinds::Key& toSet;
};
