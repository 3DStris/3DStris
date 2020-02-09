#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
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
	FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, ""));

	if (!directoryExists(sdmcArchive, homebrewPath)) {
		FSUSER_CreateDirectory(sdmcArchive, homebrewPath, 0);
	}
	if (!directoryExists(sdmcArchive, dirPath)) {
		FSUSER_CreateDirectory(sdmcArchive, dirPath, 0);
	}

	FSUSER_OpenDirectory(&dirHandle, sdmcArchive, dirPath);

	bool configFileExists = fileExists(sdmcArchive, configPath);
	if (!configFileExists) {
		FSUSER_CreateFile(sdmcArchive, configPath, 0, 0);
	}

	FSUSER_OpenFile(&configHandle, sdmcArchive, configPath,
					FS_OPEN_WRITE | FS_OPEN_READ, 0);

	if (!configFileExists) {
		save();
	}

	games.initialize(sdmcArchive);

	u64 fileSize;
	FSFILE_GetSize(configHandle, &fileSize);

	sds content = sdsnewlen("", fileSize);
	FSFILE_Read(configHandle, nullptr, 0, content, fileSize);

	rapidjson::Document document;
	document.Parse(content);
	sdsfree(content);

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

Config::~Config() {
	FSFILE_Close(configHandle);
	FSDIR_Close(dirHandle);
	FSUSER_CloseArchive(sdmcArchive);
}

void Config::save() {
	rapidjson::StringBuffer sb;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);

	this->serialize(writer);

	FSFILE_Write(configHandle, nullptr, 0, sb.GetString(), sb.GetLength(),
				 FS_WRITE_FLUSH);
	FSFILE_SetSize(configHandle, sb.GetLength());
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
