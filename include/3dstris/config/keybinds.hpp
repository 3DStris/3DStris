#pragma once

extern "C" {
#include <3ds/types.h>
}
#include <robin_hood.h>

struct mpack_writer_t;
class Keybinds final {
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
	using Binds = robin_hood::unordered_flat_map<Action, Key>;

	static const char* KEYBIND_TO_KEY[];
	static const Binds& defaults();

	Keybinds() noexcept;

	void serialize(mpack_writer_t& writer) const noexcept;

	Key get(Action action) const noexcept;
	Binds& all() noexcept;
	const Binds& all() const noexcept;

	void save() noexcept;

	bool failed() const noexcept;

   private:
	static constexpr auto KEYBINDS_PATH = "sdmc:/3ds/3dstris/keybinds.mp";

	Binds binds;

	bool _failed = false;
};
