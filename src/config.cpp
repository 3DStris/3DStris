#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <3dstris/config.hpp>
#include <3dstris/game.hpp>
#include <3dstris/states/configfailed.hpp>

static bool directoryExists(FS_Archive& archive, const FS_Path& path) {
	Handle handle;

	return !R_FAILED(FSUSER_OpenDirectory(&handle, archive, path)) &&
		   !R_FAILED(FSDIR_Close(handle));
}

static bool fileExists(FS_Archive& archive, const FS_Path& path) {
	Handle handle;

	return !R_FAILED(
			   FSUSER_OpenFile(&handle, archive, path, FS_OPEN_READ, 0)) &&
		   !R_FAILED(FSFILE_Close(handle));
}

static bool validateJson(rapidjson::Document& doc) {
	return doc.IsObject() &&								 //
		   doc.HasMember("arr") && doc["arr"].IsDouble() &&  //
		   doc.HasMember("das") && doc["das"].IsDouble();
}

Config::Config() {
	FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, ""));

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
		saveConfig(false);
	}

	u64 fileSize;
	FSFILE_GetSize(configHandle, &fileSize);

	sds configRead = sdsnewlen("", fileSize);
	FSFILE_Read(configHandle, nullptr, 0, configRead, fileSize);

	rapidjson::Document document;
	if (document.Parse<rapidjson::kParseFullPrecisionFlag>(configRead)
			.HasParseError() &&
		!validateJson(document)) {
		saveConfig();
		configFailed = true;
	}
	sdsfree(configRead);

	das = document["das"].GetDouble();
	arr = document["arr"].GetDouble();
}

Config::~Config() {
	FSFILE_Close(configHandle);
	FSDIR_Close(dirHandle);
	FSUSER_CloseArchive(sdmcArchive);
}

void Config::saveConfig(bool overwrite) {
	if (overwrite) {
		FSFILE_Close(configHandle);

		FSUSER_DeleteFile(sdmcArchive, configPath);
		FSUSER_CreateFile(sdmcArchive, configPath, 0, 0);

		FSUSER_OpenFile(&configHandle, sdmcArchive, configPath,
						FS_OPEN_WRITE | FS_OPEN_READ, 0);
	}

	rapidjson::StringBuffer sb;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);
	// writer.SetMaxDecimalPlaces(9);

	this->serialize(writer);

	FSFILE_Write(configHandle, nullptr, 0, sb.GetString(), sb.GetLength(),
				 FS_WRITE_FLUSH);
}
