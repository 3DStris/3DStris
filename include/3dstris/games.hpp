#pragma once

#include <3ds.h>
#include <sds.h>
#include <vector>

struct SavedGame {
	time_t date;
	double time;

	double pps;

	void dateString(char* buf, size_t size,
					const char* format = "%F %T") const {
		strftime(buf, size, format, localtime(&date));
	}

	bool operator<(const SavedGame& b) const { return time < b.time; }
};

using SavedGames = std::vector<SavedGame>;

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

			writer.String("pps");
			writer.Double(game.pps);

			writer.EndObject();
		}

		writer.EndArray();
	}

	const SavedGames& all() const noexcept;

	void save(const bool overwrite = true);
	void push(const SavedGame game);
	bool failed;

   private:
	FS_Path gamesPath = fsMakePath(PATH_ASCII, "/3dstris/games.json");
	SavedGames games;

	FS_Archive sdmcArchive;

	Handle gamesHandle;
};
