#include <3dstris/config.hpp>
#include <3dstris/util/fs.hpp>
#include <3dstris/util/log.hpp>

#define MEMBER_CHECK_TYPE(member, check_type, type)                    \
	LOG_INFO("Setting config member " #member);                        \
	{                                                                  \
		const auto node = mpack_node_map_cstr_optional(root, #member); \
		if (mpack_node_type(node) != mpack_type_##check_type)          \
			LOG_WARN("Failed to set config member " #member            \
					 "; using default");                               \
		else                                                           \
			member = mpack_node_##type(node);                          \
	}
#define MEMBER(member, type) MEMBER_CHECK_TYPE(member, type, type)

#define SERIALIZE_MEMBER(type, value)  \
	mpack_write_cstr(&writer, #value); \
	mpack_write_##type(&writer, value);

Config::Config() {
	if (!exists(CONFIG_PATH)) {
		LOG_INFO("Creating config file");
		save();
		l10n.loadLanguage(language);

		return;
	}

	mpack_tree_t tree;
	mpack_tree_init_filename(&tree, CONFIG_PATH, 0);
	mpack_tree_parse(&tree);
	mpack_node_t root = mpack_tree_root(&tree);

	MEMBER_CHECK_TYPE(das, uint, u16)
	MEMBER_CHECK_TYPE(arr, uint, u16)
	MEMBER_CHECK_TYPE(dropTimer, uint, u16)
	MEMBER(useTextures, bool)

	LOG_INFO("Setting config member language");
	{
		const auto node = mpack_node_map_cstr_optional(root, "language");
		if (mpack_node_type(node) != mpack_type_uint) {
			LOG_WARN("Failed to set config member language; using default");
		} else {
			language = static_cast<L10n::Language>(mpack_node_u8(node));
		}
	}

	if (mpack_tree_destroy(&tree) != mpack_ok) {
		LOG_ERROR("Failed to decode config");
		save();
		_failed = true;
	} else {
		LOG_INFO("Loaded config");
	}

	l10n.loadLanguage(language);
}

void Config::serialize(mpack_writer_t& writer) const {
	mpack_start_map(&writer, 5);

	SERIALIZE_MEMBER(u16, das)
	SERIALIZE_MEMBER(u16, arr)
	SERIALIZE_MEMBER(u16, dropTimer)
	SERIALIZE_MEMBER(bool, useTextures)
	SERIALIZE_MEMBER(u8, language)

	mpack_finish_map(&writer);
}

void Config::save() {
	LOG_INFO("Saving config");

	char* data;
	size_t size;
	mpack_writer_t writer;
	mpack_writer_init_growable(&writer, &data, &size);

	this->serialize(writer);

	if (mpack_writer_destroy(&writer) != mpack_ok) {
		LOG_ERROR("Failed to encode config");
		return;
	}

	FILE* file = fopen(CONFIG_PATH, "w");
	fwrite(data, sizeof(char), size, file);
	fclose(file);

	delete[] data;

	LOG_INFO("Saved config");
}

Games& Config::getGames() noexcept {
	return games;
}

L10n& Config::getL10n() noexcept {
	return l10n;
}
const L10n& Config::getL10n() const noexcept {
	return l10n;
}

Keybinds& Config::getKeybinds() noexcept {
	return keybinds;
}
const Keybinds& Config::getKeybinds() const noexcept {
	return keybinds;
}

bool Config::failed() const noexcept {
	return _failed;
};
