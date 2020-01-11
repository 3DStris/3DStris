#pragma once

#include <3ds.h>

struct Config {
	Config();
	~Config();

	template <typename Writer>
	void serialize(Writer& writer) const {
		writer.StartObject();

		writer.String("das");
		writer.Double(das);

		writer.String("arr");
		writer.Double(arr);

		writer.EndObject();
	}

	void saveConfig(bool overwrite = true);

	double das = 0.2;
	double arr = 0.0;

	bool configFailed = false;

   private:
	const FS_Path dirPath = fsMakePath(PATH_ASCII, "/3dstris");
	const FS_Path configPath = fsMakePath(PATH_ASCII, "/3dstris/config.json");

	FS_Archive sdmcArchive;

	Handle dirHandle;
	Handle configHandle;
};
