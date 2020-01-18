#pragma once

#include <3ds.h>

#include <3dstris/games.hpp>

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

		writer.EndObject();
	}

	void save();
	Games& getGames() noexcept;

	u32 das = 200;
	u32 arr = 0;
	u32 dropTimer = 5;

	bool failed = false;

   private:
	const FS_Path homebrewPath = fsMakePath(PATH_ASCII, "/3ds/");
	const FS_Path dirPath = fsMakePath(PATH_ASCII, "/3ds/3dstris");
	const FS_Path configPath =
		fsMakePath(PATH_ASCII, "/3ds/3dstris/config.json");

	Games games;

	FS_Archive sdmcArchive;

	Handle dirHandle;
	Handle configHandle;
};
