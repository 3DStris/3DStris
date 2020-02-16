#pragma once

#include <3dstris/config/games.hpp>
#include <3dstris/config/keybinds.hpp>
#include <3dstris/config/l10n.hpp>
#include <memory>

struct Config {
	Config();

	template <typename Writer>
	void serialize(Writer& writer) const {
		writer.StartObject();

		writer.String("das");
		writer.Uint(das);

		writer.String("arr");
		writer.Uint(arr);

		writer.String("dropTimer");
		writer.Uint(dropTimer);

		writer.String("useTextures");
		writer.Bool(useTextures);

		writer.String("language");
		writer.String(L10n::languageToString(language));

		writer.EndObject();
	}

	void save();

	Games& getGames() noexcept;

	L10n& getL10n() noexcept;
	const L10n& getL10n() const noexcept;

	Keybinds& getKeybinds() noexcept;
	const Keybinds& getKeybinds() const noexcept;

	bool failed() const noexcept;

	u32 das = 200;
	u32 arr = 0;
	u32 dropTimer = 5;
	bool useTextures = true;
	L10n::Language language = L10n::EN;

   private:
	static constexpr auto CONFIG_PATH = "sdmc:/3ds/3dstris/config.json";
	const FS_Path homebrewPath = fsMakePath(PATH_ASCII, "/3ds/");
	const FS_Path dirPath = fsMakePath(PATH_ASCII, "/3ds/3dstris");
	const FS_Path configPath =
		fsMakePath(PATH_ASCII, "/3ds/3dstris/config.json");

	Games games;
	L10n l10n;
	Keybinds keybinds;

	bool _failed = false;
};
