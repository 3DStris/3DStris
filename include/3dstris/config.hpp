#pragma once

#include <3ds.h>
#include <sds.h>
#include <3dstris/games.hpp>
#include <3dstris/util/l10n.hpp>
#include <memory>

struct Config {
	Config();
	~Config();

	template <typename Writer>
	void serialize(Writer& writer) const {
		writer.StartObject();

		writer.String("das");
		writer.Uint(das);

		writer.String("arr");
		writer.Uint(arr);

		writer.String("dropTimer");
		writer.Uint(dropTimer);

		writer.String("language");
		writer.String(L10n::languageToString(language));

		writer.EndObject();
	}

	void save();

	Games& getGames() noexcept { return games; }

	L10n& getL10n() noexcept { return *l10n; }
	const L10n& getL10n() const noexcept { return *l10n; }

	u32 das = 200;
	u32 arr = 0;
	u32 dropTimer = 5;
	L10n::Language language = L10n::EN;

	bool failed() const noexcept { return _failed; }

   private:
	const FS_Path homebrewPath = fsMakePath(PATH_ASCII, "/3ds/");
	const FS_Path dirPath = fsMakePath(PATH_ASCII, "/3ds/3dstris");
	const FS_Path configPath =
		fsMakePath(PATH_ASCII, "/3ds/3dstris/config.json");

	Games games;
	std::unique_ptr<L10n> l10n;

	FS_Archive sdmcArchive;

	Handle dirHandle;
	Handle configHandle;

	bool _failed = false;
};
