#include <3dstris/config/keybinds.hpp>
#include <3dstris/util/fs.hpp>
#include <3dstris/util/log.hpp>

const char* Keybinds::KEYBIND_TO_KEY[]{
	"keybindselect.left",	 "keybindselect.right",
	"keybindselect.rotatecw", "keybindselect.rotateccw",
	"keybindselect.softdrop", "keybindselect.harddrop",
	"keybindselect.hold"};

const Keybinds::Binds Keybinds::DEFAULT_BINDS{
	{LEFT, KEY_LEFT},	 {RIGHT, KEY_RIGHT},	{ROTATE_CW, KEY_B},
	{ROTATE_CCW, KEY_Y},  {SOFT_DROP, KEY_DOWN}, {HARD_DROP, KEY_UP},
	{HOLD, KEY_A | KEY_X}};

Keybinds::Keybinds() : binds(DEFAULT_BINDS) {
	LOG_INFO("Loading keybinds");
	if (!exists(KEYBINDS_PATH)) {
		LOG_INFO("Creating keybinds file");
		save();

		return;
	}

	mpack_tree_t tree;
	mpack_tree_init_filename(&tree, KEYBINDS_PATH, 0);
	mpack_tree_parse(&tree);
	mpack_node_t root = mpack_tree_root(&tree);

	for (size_t i = 0; i < mpack_node_map_count(root); ++i) {
		const auto _key = mpack_node_map_key_at(root, i);
		const auto _value = mpack_node_map_value_at(root, i);
		if (mpack_node_type(_key) != mpack_type_uint ||
			mpack_node_type(_value) != mpack_type_uint) {
			continue;
		}

		const auto key = static_cast<Action>(mpack_node_u8(_key));
		const auto value = mpack_node_u32(_value);
		binds[key] = value;
	}

	if (mpack_tree_destroy(&tree) != mpack_ok) {
		LOG_ERROR("Failed to decode keybinds");
		save();
		_failed = true;
	} else {
		LOG_INFO("Loaded keybinds");
	}
}

void Keybinds::serialize(mpack_writer_t& writer) const {
	mpack_start_map(&writer, binds.size());

	for (const auto& bind : binds) {
		mpack_write_u8(&writer, bind.first);
		mpack_write_u32(&writer, bind.second);
	}

	mpack_finish_map(&writer);
}

Keybinds::Key Keybinds::get(const Action action) const noexcept {
	return binds.at(action);
}
Keybinds::Binds& Keybinds::all() noexcept {
	return binds;
}
const Keybinds::Binds& Keybinds::all() const noexcept {
	return binds;
}

void Keybinds::save() {
	LOG_INFO("Saving keybinds");

	char* data;
	size_t size;
	mpack_writer_t writer;
	mpack_writer_init_growable(&writer, &data, &size);

	this->serialize(writer);

	if (mpack_writer_destroy(&writer) != mpack_ok) {
		LOG_ERROR("Failed to encode keybinds");
		return;
	}

	FILE* file = fopen(KEYBINDS_PATH, "w");
	fwrite(data, sizeof(char), size, file);
	fclose(file);

	delete[] data;

	LOG_INFO("Saved keybinds");
}

bool Keybinds::failed() const noexcept {
	return _failed;
}
