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

	try {
		nlohmann::json configJson = nlohmann::json::parse(configRead);
		sdsfree(configRead);

		das = configJson["das"].get<double>();
		arr = configJson["arr"].get<double>();
	} catch (const std::exception&) {
		saveConfig();
		configFailed = true;
	}
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

	nlohmann::json config = {{"das", das}, {"arr", arr}};
	const auto configString = config.dump(4, ' ', true);

	FSFILE_Write(configHandle, nullptr, 0, configString.c_str(),
				 strlen(configString.c_str()), FS_WRITE_FLUSH);
}
