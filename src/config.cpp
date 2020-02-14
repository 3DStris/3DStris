#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/writer.h>
#include <3dstris/config.hpp>
#include <3dstris/game.hpp>
#include <3dstris/states/loadfailed.hpp>

#define MEMBER(member, type)                                         \
	if (document.HasMember(#member) && document[#member].Is##type()) \
		member = document[#member].Get##type();

static bool directoryExists(FS_Archive archive, const FS_Path& path) {
	Handle handle;

	return R_SUCCEEDED(FSUSER_OpenDirectory(&handle, archive, path)) &&
		   R_SUCCEEDED(FSDIR_Close(handle));
}

static bool fileExists(FS_Archive archive, const FS_Path& path) {
	Handle handle;

	return R_SUCCEEDED(
			   FSUSER_OpenFile(&handle, archive, path, FS_OPEN_READ, 0)) &&
		   R_SUCCEEDED(FSFILE_Close(handle));
}

static bool validateJson(const rapidjson::Document& doc) {
	return !doc.HasParseError();
}

Config::Config() {
	FS_Archive sdmcArchive;

	FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, ""));

	if (!directoryExists(sdmcArchive, homebrewPath)) {
		FSUSER_CreateDirectory(sdmcArchive, homebrewPath, 0);
	}
	if (!directoryExists(sdmcArchive, dirPath)) {
		FSUSER_CreateDirectory(sdmcArchive, dirPath, 0);
	}

	bool configFileExists = fileExists(sdmcArchive, configPath);
	if (!configFileExists) {
		FSUSER_CreateFile(sdmcArchive, configPath, 0, 0);
	}

	if (!configFileExists) {
		save();
	}

	games.initialize(sdmcArchive);
	FSUSER_CloseArchive(sdmcArchive);

	FILE* file = fopen(CONFIG_PATH, "r");

	char readBuffer[128];
	rapidjson::FileReadStream fileStream(file, readBuffer, sizeof(readBuffer));

	rapidjson::Document document;
	document.ParseStream(fileStream);

	fclose(file);

	if (!validateJson(document)) {
		save();
		_failed = true;
	} else {
		MEMBER(das, Uint)
		MEMBER(arr, Uint)
		MEMBER(dropTimer, Uint)
		MEMBER(useTextures, Bool)

		if (document.HasMember("language") && document["language"].IsString()) {
			language = L10n::stringToLanguage(document["language"].GetString());
		}
	}

	l10n.loadLanguage(language);
}

void Config::save() {
	FILE* file = fopen(CONFIG_PATH, "w");

	char writeBuffer[128];
	rapidjson::FileWriteStream fileStream(file, writeBuffer,
										  sizeof(writeBuffer));

	rapidjson::Writer<rapidjson::FileWriteStream> writer(fileStream);
	writer.SetMaxDecimalPlaces(4);
	this->serialize(writer);

	fclose(file);
}

Games& Config::getGames() noexcept {
	return games;
}

L10n& Config::getL10n() noexcept {
	return l10n;
}
const L10n& Config::getL10n() const noexcept {
	return l10n;
}

bool Config::failed() const noexcept {
	return _failed;
};
