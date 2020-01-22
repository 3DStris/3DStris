#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <sds.h>
#include <3dstris/config.hpp>
#include <3dstris/games.hpp>
#include <algorithm>

static bool fileExists(FS_Archive& archive, const FS_Path& path) {
	Handle handle;

	return R_SUCCEEDED(
			   FSUSER_OpenFile(&handle, archive, path, FS_OPEN_READ, 0)) &&
		   R_SUCCEEDED(FSFILE_Close(handle));
}

static bool validateJson(rapidjson::Document& doc) {
	return !doc.HasParseError();
}

void Games::initialize(const FS_Archive sdmcArchive) {
	this->sdmcArchive = sdmcArchive;

	bool gamesFileExists = fileExists(this->sdmcArchive, gamesPath);
	if (!gamesFileExists) {
		FSUSER_CreateFile(this->sdmcArchive, gamesPath, 0, 0);
	}

	FSUSER_OpenFile(&gamesHandle, this->sdmcArchive, gamesPath,
					FS_OPEN_WRITE | FS_OPEN_READ, 0);

	if (!gamesFileExists) {
		save();
	}

	u64 fileSize;
	FSFILE_GetSize(gamesHandle, &fileSize);

	sds configRead = sdsnewlen("", fileSize);
	FSFILE_Read(gamesHandle, nullptr, 0, configRead, fileSize);

	rapidjson::Document document;
	document.Parse<rapidjson::kParseFullPrecisionFlag>(configRead);
	sdsfree(configRead);

	if (!validateJson(document)) {
		save();
		failed = true;

		return;
	} else {
		for (const auto& object : document.GetArray()) {
			if (object.FindMember("time") != object.MemberEnd() &&
				object.FindMember("date") != object.MemberEnd() &&
				object.FindMember("pps") != object.MemberEnd()) {
				games.push_back({object["date"].GetInt64(),   //
								 object["time"].GetDouble(),  //
								 object["pps"].GetDouble()});
			}
		}
		std::sort(games.begin(), games.end(), std::less<SavedGame>());
	}
}

Games::~Games() {
	FSFILE_Close(gamesHandle);
}

const SavedGames& Games::all() const noexcept {
	return games;
}

void Games::push(SavedGame&& game) {
	games.push_back(game);
	std::sort(games.begin(), games.end(), std::less<SavedGame>());
}

void Games::save() {
	rapidjson::StringBuffer sb;
	rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
	writer.SetMaxDecimalPlaces(4);

	this->serialize(writer);

	FSFILE_Write(gamesHandle, nullptr, 0, sb.GetString(), sb.GetLength(),
				 FS_WRITE_FLUSH);
	FSFILE_SetSize(gamesHandle, sb.GetLength());
}
