#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/writer.h>
#include <3dstris/game.hpp>
#include <3dstris/util/fs.hpp>
#include <3dstris/util/log.hpp>
#include <3dstris/version.hpp>

#define MEMBER(member, type)                                         \
	if (document.HasMember(#member) && document[#member].Is##type()) \
		member = document[#member].Get##type();

static bool validateJson(const rapidjson::Document& doc) {
	return !doc.HasParseError() && doc.IsObject();
}

Config::Config() {
	FS_Archive sdmcArchive;

	FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, ""));

	if (!directoryExists(sdmcArchive, homebrewPath)) {
		LOG_INFO("Creating /3ds/");
		FSUSER_CreateDirectory(sdmcArchive, homebrewPath, 0);
	}
	if (!directoryExists(sdmcArchive, dirPath)) {
		LOG_INFO("Creating 3DStris dir");
		FSUSER_CreateDirectory(sdmcArchive, dirPath, 0);
	}

	Log::get().load(sdmcArchive);

	if (!fileExists(sdmcArchive, configPath)) {
		LOG_INFO("Creating config file");
		FSUSER_CreateFile(sdmcArchive, configPath, 0, 0);
		save();
	}

	games.initialize(sdmcArchive);
	keybinds.initialize(sdmcArchive);

	FSUSER_CloseArchive(sdmcArchive);

	FILE* file = fopen(CONFIG_PATH, "r");

	char readBuffer[128];
	rapidjson::FileReadStream fileStream(file, readBuffer, sizeof readBuffer);

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
										  sizeof writeBuffer);

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

Keybinds& Config::getKeybinds() noexcept {
	return keybinds;
}
const Keybinds& Config::getKeybinds() const noexcept {
	return keybinds;
}

bool Config::failed() const noexcept {
	return _failed;
};
