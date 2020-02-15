#pragma once

#include <3ds.h>
#include <parallel_hashmap/btree.h>

class Keybinds {
   public:
	using Key = u32;

	enum Action {
		LEFT,
		RIGHT,
		ROTATE_CW,
		ROTATE_CCW,
		SOFT_DROP,
		HARD_DROP,
		HOLD
	};

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

	void save();

	bool failed() const noexcept;

   private:
	phmap::btree_map<Action, Key> binds;

	static constexpr auto KEYBINDS_PATH = "sdmc:/3ds/3dstris/keybinds.json";
	const FS_Path keybindsFSPath =
		fsMakePath(PATH_ASCII, "/3ds/3dstris/keybinds.json");

	bool _failed = false;
};
