#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>

#include <3dstris/config/games.hpp>
#include <3dstris/util/fs.hpp>
#include <3dstris/util/log.hpp>

#define MEMBER_CHECK_TYPE(value, type, check_type)                        \
	type value;                                                           \
	{                                                                     \
		const auto _##value = mpack_node_map_cstr_optional(game, #value); \
		if (mpack_node_type(_##value) != mpack_type_##check_type) {       \
			LOG_WARN("Found invalid game at index %u, discarding", i);    \
			saveAfterLoad = true;                                         \
			continue;                                                     \
		}                                                                 \
		value = mpack_node_##type(_##value);                              \
	}
#define MEMBER(value, type) MEMBER_CHECK_TYPE(value, type, type)

// Yes, I copy pasted the previous macro just to change 3 lines. I can't think
// of any weird macro hack I can do to avoid doing this, sorry..
#define MEMBER_CHECK_TYPE_OPTIONAL(value, type, check_type, _default)     \
	type value;                                                           \
	{                                                                     \
		const auto _##value = mpack_node_map_cstr_optional(game, #value); \
		value = mpack_node_type(_##value) != mpack_type_##check_type      \
					? _default                                            \
					: mpack_node_##type(_##value);                        \
	}
#define MEMBER_OPTIONAL(value, type, _default) \
	MEMBER_CHECK_TYPE_OPTIONAL(value, type, type, _default)

#define SERIALIZE_MEMBER(value, type)  \
	mpack_write_cstr(&writer, #value); \
	mpack_write_##type(&writer, game.value);

constexpr u8 DEFAULT_LINES = 20;

static bool validateJson(const rapidjson::Document& doc) {
	return !doc.HasParseError() && doc.IsArray();
}

static bool validateGame(
	const rapidjson::GenericValue<rapidjson::UTF8<char>>& game) {
	return game.FindMember("time") != game.MemberEnd() &&
		   game.FindMember("date") != game.MemberEnd() &&
		   game.FindMember("pps") != game.MemberEnd();
}

Games::Games() noexcept {
	static constexpr auto GAMES_JSON_PATH = "sdmc:/3ds/3dstris/games.json";

	LOG_INFO("Loading games");

	if (exists(GAMES_JSON_PATH) && !exists(GAMES_PATH)) {
		LOG_INFO(
			"Found games.json but not games.mp; loading from JSON, saving as "
			"MP");

		FILE* file = fopen(GAMES_JSON_PATH, "r");

		char readBuffer[1024];
		rapidjson::FileReadStream fileStream(file, readBuffer,
											 sizeof readBuffer);

		rapidjson::Document document;
		document.ParseStream(fileStream);

		fclose(file);

		if (!validateJson(document)) {
			LOG_ERROR("Failed to load games");
			save();
			_failed = true;

			return;
		}
		LOG_DEBUG("Reserving space for %u games", document.Size());
		games.reserve(document.Size());

		for (const auto& object : document.GetArray()) {
			if (validateGame(object)) {
				games.push_back({object["time"].GetDouble(),
								 object["pps"].GetDouble(),
								 object["date"].GetInt64(), DEFAULT_LINES});
			}
		}

		save();
		return;
	} else if (!exists(GAMES_PATH)) {
		LOG_INFO("Creating games file");
		save();
		return;
	}

	s32 mainPrio;
	svcGetThreadPriority(&mainPrio, CUR_THREAD_HANDLE);
	loadThread = threadCreate(
		[](void* _games) {
			auto& _this = *static_cast<Games*>(_games);

			mpack_tree_t tree;
			mpack_tree_init_filename(&tree, GAMES_PATH, 0);
			mpack_tree_parse(&tree);
			mpack_node_t root = mpack_tree_root(&tree);

			bool saveAfterLoad = false;
			const size_t length = mpack_node_array_length(root);
			LOG_DEBUG("Reserving space for %u games", length);
			_this.games.reserve(length);
			for (size_t i = 0; i < length; ++i) {
				const auto game = mpack_node_array_at(root, i);
				if (mpack_node_type(game) != mpack_type_map) {
					LOG_WARN("Found invalid game at index %u, discarding", i);
					saveAfterLoad = true;
					continue;
				}

				using i64 = long long;
				MEMBER_CHECK_TYPE(date, i64, uint)
				MEMBER(time, double)
				MEMBER(pps, double)
				MEMBER_CHECK_TYPE_OPTIONAL(lines, u16, uint, DEFAULT_LINES)
				_this.games.push_back({time, pps, date, lines});
			}

			if (saveAfterLoad) {
				LOG_WARN("Saving due to discarded games");
				_this.save();
			}

			if (mpack_tree_destroy(&tree) != mpack_ok) {
				LOG_ERROR("Failed to decode games, error code %u",
						  mpack_tree_error(&tree));
				_this.save();
				_this._failed = true;
			} else {
				LOG_INFO("Loaded games");
			}

			// Just in case
			_this.saveThread = nullptr;
		},
		this, 1024, mainPrio + 1, -2, true);
}

void Games::serialize(mpack_writer_t& writer) const noexcept {
	mpack_start_array(&writer, games.size());

	for (const auto& game : games) {
		mpack_start_map(&writer, game.lines != DEFAULT_LINES ? 4 : 3);

		SERIALIZE_MEMBER(time, double)
		SERIALIZE_MEMBER(date, i64)
		SERIALIZE_MEMBER(pps, double)
		if (game.lines != DEFAULT_LINES) {
			SERIALIZE_MEMBER(lines, u16)
		}

		mpack_finish_map(&writer);
	}

	mpack_finish_array(&writer);
}

const Games::SavedGames& Games::all() const noexcept {
	joinLoadThread();
	return games;
}

void Games::push(SavedGame&& game) {
	games.push_back(game);
}

void Games::save() noexcept {
	LOG_INFO("Saving games");

	if (saveThread) {
		LOG_INFO("Waiting for previous save thread to finish...");
		joinSaveThread();
	}

	s32 mainPrio;
	svcGetThreadPriority(&mainPrio, CUR_THREAD_HANDLE);
	saveThread = threadCreate(
		[](void* _this) {
			char* data;
			size_t size;
			mpack_writer_t writer;
			mpack_writer_init_growable(&writer, &data, &size);

			static_cast<Games*>(_this)->serialize(writer);

			if (mpack_writer_destroy(&writer) != mpack_ok) {
				LOG_ERROR("Failed to encode games, error code %u",
						  mpack_writer_error(&writer));
				return;
			}

			FILE* file = fopen(GAMES_PATH, "w");
			fwrite(data, sizeof(char), size, file);
			fclose(file);

			delete[] data;

			LOG_INFO("Saved games");

			// Just in case
			static_cast<Games*>(_this)->saveThread = nullptr;
		},
		this, 1024, mainPrio + 1, -2, true);
}

bool Games::failed() const noexcept {
	return _failed;
}
