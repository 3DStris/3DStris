#pragma once

#include <3ds.h>
#include <vector>

struct SavedGame {
	u64 date;
	double time;

	double pps;
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
			writer.Uint64(game.date);

			writer.String("pps");
			writer.Double(game.pps);

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
