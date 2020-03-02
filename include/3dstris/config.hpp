#pragma once

#include <3dstris/config/games.hpp>
#include <3dstris/config/keybinds.hpp>
#include <3dstris/config/l10n.hpp>
#include <memory>

struct Config {
	Config();

	void serialize(mpack_writer_t& writer) const;

	void save();

	Games& getGames() noexcept;

	L10n& getL10n() noexcept;
	const L10n& getL10n() const noexcept;

	Keybinds& getKeybinds() noexcept;
	const Keybinds& getKeybinds() const noexcept;

	bool failed() const noexcept;

	u16 das = 200;
	u16 arr = 0;
	u16 dropTimer = 5;
	bool useTextures = true;
	L10n::Language language = L10n::Language::EN;

   private:
	static constexpr auto CONFIG_PATH = "sdmc:/3ds/3dstris/config.mp";

	Games games;
	L10n l10n;
	Keybinds keybinds;

	bool _failed = false;
};
