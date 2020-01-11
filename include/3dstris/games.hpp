#pragma once

#include <3ds.h>
#include <vector>

struct SavedGame {
	time_t date;
	double time;
};

class Games {
   public:
	~Games();
	void initialize(const FS_Archive sdmcArchive);

	template <typename Writer>
	void serialize(Writer& writer) const {
		writer.StartArray();

		for (const auto& game : games) {
			writer.StartObject();

			writer.String("time");
			writer.Double(game.time);

			writer.String("date");
			writer.Int64(game.date);

			writer.EndObject();
		}

		writer.EndArray();
	}

	const std::vector<SavedGame>& all() const noexcept;
	void save(const bool overwrite = true);
	void push(const SavedGame game);

	bool failed;

   private:
	FS_Path gamesPath = fsMakePath(PATH_ASCII, "/3dstris/games.json");
	std::vector<SavedGame> games;

	FS_Archive sdmcArchive;

	Handle gamesHandle;
};
