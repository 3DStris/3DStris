#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/writer.h>
#include <sds.h>
#include <3dstris/config/games.hpp>
#include <3dstris/util/fs.hpp>
#include <3dstris/util/log.hpp>
#include <algorithm>

static bool validateJson(const rapidjson::Document& doc) {
	return !doc.HasParseError() && doc.IsArray();
}

static bool validateGame(
	const rapidjson::GenericValue<rapidjson::UTF8<char>>& game) {
	return game.FindMember("time") != game.MemberEnd() &&
		   game.FindMember("date") != game.MemberEnd() &&
		   game.FindMember("pps") != game.MemberEnd();
}

void Games::initialize(const FS_Archive sdmcArchive) {
	LOG_INFO("Loading games");
	if (!fileExists(sdmcArchive, gamesFSPath)) {
		LOG_INFO("Creating games file");
		FSUSER_CreateFile(sdmcArchive, gamesFSPath, 0, 0);
		save();
	}

	FILE* file = fopen(GAMES_PATH, "r");

	char readBuffer[1024];
	rapidjson::FileReadStream fileStream(file, readBuffer, sizeof readBuffer);

	rapidjson::Document document;
	document.ParseStream(fileStream);

	fclose(file);

	if (!validateJson(document)) {
		LOG_ERROR("Failed to load games");
		save();
		_failed = true;
	} else {
		LOG_DEBUG("Reserving space for %u games", document.Size());
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
	LOG_INFO("Saving games");

	s32 mainPrio;
	svcGetThreadPriority(&mainPrio, CUR_THREAD_HANDLE);

	threadCreate(
		[](void* games) {
			FILE* file = fopen(GAMES_PATH, "w");

			char writeBuffer[1024];
			rapidjson::FileWriteStream fileStream(file, writeBuffer,
												  sizeof writeBuffer);

			rapidjson::Writer<rapidjson::FileWriteStream> writer(fileStream);
			writer.SetMaxDecimalPlaces(4);
			static_cast<Games*>(games)->serialize(writer);

			fclose(file);

			LOG_INFO("Saved games");
		},
		this, 2048, mainPrio - 1, -2, true);
}

bool Games::failed() const noexcept {
	return _failed;
}
