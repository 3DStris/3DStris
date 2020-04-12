#pragma once

#include <3dstris/config/games.hpp>
#include <3dstris/config/keybinds.hpp>
#include <3dstris/config/l10n.hpp>
#include <3dstris/gui/theme.hpp>

struct BaseConfig {
	u16 das = 200;
	u16 arr = 0;
	u16 dropTimer = 5;
	bool useTextures = true;
	L10n::Language language = L10n::Language(L10n::EN_US);
	Theme theme = Theme::night();
};

class Config final : public BaseConfig {
   public:
	Config() noexcept;
	~Config() noexcept;

	void operator=(BaseConfig& other) noexcept {
		das = other.das;
		arr = other.arr;
		dropTimer = other.dropTimer;
		useTextures = other.useTextures;
		language = other.language;
		theme = other.theme;
	}

	void serialize(mpack_writer_t& writer) const noexcept;

	void save() noexcept;

	Games& getGames() noexcept;

	L10n& getL10n() noexcept;
	const L10n& getL10n() const noexcept;

	Keybinds& getKeybinds() noexcept;
	const Keybinds& getKeybinds() const noexcept;

	bool failed() const noexcept;

   private:
	static constexpr auto CONFIG_PATH = "sdmc:/3ds/3dstris/config.mp";

	Games games;
	L10n l10n;
	Keybinds keybinds;

	bool _failed = false;
};
