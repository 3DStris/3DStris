#pragma once

extern "C" {
#include <3ds/thread.h>
}
#include <mpack/mpack.h>
#include <time.h>

#include <vector>

struct SavedGame {
	double time;
	double pps;
	time_t date;
	u16 lines;

	void dateString(char* __restrict buf, size_t size,
					const char* __restrict format = "%F %T") const {
		strftime(buf, size, format, localtime(&date));
	}

	bool operator<(const SavedGame& b) const {
		return lines < b.lines || time < b.time;
	}
};

class Games final {
   public:
	using SavedGames = std::vector<SavedGame>;

	Games() noexcept;

	void serialize(mpack_writer_t& writer) const noexcept;

	SavedGames& all() noexcept;

	void save() noexcept;
	void push(SavedGame&& game);

	inline void joinSaveThread() const noexcept {
		// Wait up to 30 seconds for the save thread to finish. This is to
		// prevent any possible segfaults or loss of data. If it ever takes
		// longer than 30 seconds, we've got a bigger problem on our hands..
		threadJoin(saveThread, 30 * 1000000000ull);
	}

	inline void joinLoadThread() const noexcept {
		threadJoin(loadThread, 30 * 1000000000ull);
	}

	bool failed() const noexcept;

   private:
	static constexpr auto GAMES_PATH = "sdmc:/3ds/3dstris/games.mp";

	SavedGames games;

	Thread loadThread = nullptr;
	Thread saveThread = nullptr;

	bool _failed = false;
};
