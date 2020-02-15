#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/writer.h>
#include <sds.h>
#include <3dstris/config.hpp>
#include <3dstris/games.hpp>
#include <algorithm>

static bool fileExists(FS_Archive archive, const FS_Path& path) {
	Handle handle;

	return R_SUCCEEDED(
			   FSUSER_OpenFile(&handle, archive, path, FS_OPEN_READ, 0)) &&
		   R_SUCCEEDED(FSFILE_Close(handle));
}

static bool validateJson(const rapidjson::Document& doc) {
	return !doc.HasParseError();
}

static bool validateGame(
	const rapidjson::GenericValue<rapidjson::UTF8<char>>& game) {
	return game.FindMember("time") != game.MemberEnd() &&
		   game.FindMember("date") != game.MemberEnd() &&
		   game.FindMember("pps") != game.MemberEnd();
}

void Games::initialize(const FS_Archive sdmcArchive) {
	this->sdmcArchive = sdmcArchive;

	const bool gamesFileExists = fileExists(this->sdmcArchive, gamesFSPath);
	if (!gamesFileExists) {
		FSUSER_CreateFile(this->sdmcArchive, gamesFSPath, 0, 0);
	}

	if (!gamesFileExists) {
		save();
	}

	FILE* file = fopen(GAMES_PATH, "r");

	char readBuffer[1024];
	rapidjson::FileReadStream fileStream(file, readBuffer, sizeof(readBuffer));

	rapidjson::Document document;
	document.ParseStream(fileStream);

	fclose(file);

	if (!validateJson(document)) {
		save();
		_failed = true;
	} else {
		games.reserve(document.GetArray().Size());

		for (const auto& object : document.GetArray()) {
			if (validateGame(object)) {
				games.push_back({object["date"].GetInt64(),   //
								 object["time"].GetDouble(),  //
								 object["pps"].GetDouble()});
			}
		}
		std::sort(games.begin(), games.end(), std::less<SavedGame>());
	}
}

const SavedGames& Games::all() const noexcept {
	return games;
}

void Games::push(SavedGame&& game) {
	games.push_back(game);
	std::sort(games.begin(), games.end(), std::less<SavedGame>());
}

void Games::save() {
	s32 mainPrio;
	svcGetThreadPriority(&mainPrio, CUR_THREAD_HANDLE);

	threadCreate(
		[](void* games) {
			FILE* file = fopen(GAMES_PATH, "w");

			char writeBuffer[1024];
			rapidjson::FileWriteStream fileStream(file, writeBuffer,
												  sizeof(writeBuffer));

			rapidjson::Writer<rapidjson::FileWriteStream> writer(fileStream);
			writer.SetMaxDecimalPlaces(4);
			static_cast<Games*>(games)->serialize(writer);

			fclose(file);
		},
		this, 2048, mainPrio - 1, -2, true);
}

bool Games::failed() const noexcept {
	return _failed;
}
