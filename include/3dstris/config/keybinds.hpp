#pragma once

#include <3ds.h>
#include <parallel_hashmap/btree.h>

class Keybinds {
   public:
	enum Action {
		LEFT,
		RIGHT,
		ROTATE_CW,
		ROTATE_CCW,
		SOFT_DROP,
		HARD_DROP,
		HOLD
	};

	using Key = u32;
	using Binds = phmap::btree_map<Action, Key>;

	const static char* KEYBIND_TO_KEY[];

	Keybinds();

	void initialize(const FS_Archive sdmcArchive);

	template <typename Writer>
	void serialize(Writer& writer) const {
		writer.StartObject();

		for (const auto& bind : binds) {
			char buf[2];
			writer.String(utoa(bind.first, buf, 10));
			writer.Uint(bind.second);
		}

		writer.EndObject();
	}

	Key get(const Action action) const noexcept;
	Binds& all() noexcept;
	const Binds& all() const noexcept;

	void save();

	bool failed() const noexcept;

   private:
	Binds binds;

	static constexpr auto KEYBINDS_PATH = "sdmc:/3ds/3dstris/keybinds.json";
	const FS_Path keybindsFSPath =
		fsMakePath(PATH_ASCII, "/3ds/3dstris/keybinds.json");

	bool _failed = false;
};
