#pragma once

#include <3ds/types.h>
#include <mpack/mpack.h>
#include <parallel_hashmap/phmap.h>

class Keybinds {
   public:
	enum class Action {
		LEFT,
		RIGHT,
		ROTATE_CW,
		ROTATE_CCW,
		SOFT_DROP,
		HARD_DROP,
		HOLD
	};

	using Key = u32;
	using Binds = phmap::flat_hash_map<Action, Key>;

	const static char* KEYBIND_TO_KEY[];
	const static Binds DEFAULT_BINDS;

	Keybinds();

	void serialize(mpack_writer_t& writer) const;

	Key get(const Action action) const noexcept;
	Binds& all() noexcept;
	const Binds& all() const noexcept;

	void save();

	bool failed() const noexcept;

   private:
	static constexpr auto KEYBINDS_PATH = "sdmc:/3ds/3dstris/keybinds.mp";

	Binds binds;

	bool _failed = false;
};
