#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/writer.h>
#include <sds.h>
#include <3dstris/config/keybinds.hpp>
#include <3dstris/util/fs.hpp>
#include <3dstris/util/log.hpp>

static bool validateJson(const rapidjson::Document& doc) {
	return !doc.HasParseError() && doc.IsObject();
}

const char* Keybinds::KEYBIND_TO_KEY[]{
	"keybindselect.left",	 "keybindselect.right",
	"keybindselect.rotatecw", "keybindselect.rotateccw",
	"keybindselect.softdrop", "keybindselect.harddrop",
	"keybindselect.hold"};

const Keybinds::Binds Keybinds::DEFAULT_BINDS{
	{LEFT, KEY_LEFT},	 {RIGHT, KEY_RIGHT},	{ROTATE_CW, KEY_B},
	{ROTATE_CCW, KEY_Y},  {SOFT_DROP, KEY_DOWN}, {HARD_DROP, KEY_UP},
	{HOLD, KEY_A | KEY_X}};

Keybinds::Keybinds() : binds(DEFAULT_BINDS) {}

void Keybinds::initialize(const FS_Archive sdmcArchive) {
	LOG_INFO("Loading keybinds");
	if (!fileExists(sdmcArchive, keybindsFSPath)) {
		LOG_INFO("Creating keybinds file");
		FSUSER_CreateFile(sdmcArchive, keybindsFSPath, 0, 0);
		save();
	}

	FILE* file = fopen(KEYBINDS_PATH, "r");

	char readBuffer[64];
	rapidjson::FileReadStream fileStream(file, readBuffer, sizeof readBuffer);

	rapidjson::Document document;
	document.ParseStream(fileStream);

	fclose(file);

	if (!validateJson(document)) {
		save();
		_failed = true;
	} else {
		for (const auto& object : document.GetObject()) {
			const Action index =
				static_cast<Action>(atoi(object.name.GetString()));
			const Key key = object.value.GetUint();
			if (binds[index] != key) {
				binds[index] = key;
			}
		}
	}
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

	FILE* file = fopen(KEYBINDS_PATH, "w");

	char writeBuffer[64];
	rapidjson::FileWriteStream fileStream(file, writeBuffer,
										  sizeof writeBuffer);

	rapidjson::Writer<rapidjson::FileWriteStream> writer(fileStream);
	this->serialize(writer);

	fclose(file);

	LOG_INFO("Saved keybinds");
}

bool Keybinds::failed() const noexcept {
	return _failed;
}
