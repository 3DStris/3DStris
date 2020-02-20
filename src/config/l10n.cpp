#include <rapidjson/filereadstream.h>

#include <3dstris/config/l10n.hpp>

constexpr std::array<L10n::Language, 8> L10n::LANGUAGES;

const std::array<char[2 + 1], 8> L10n::LANGUAGE_TO_STRING = {
	"en", "bg", "ru", "pt", "pl", "de", "jp", "mk"};

const phmap::btree_map<const char*, L10n::Language, L10n::CompareString>
	L10n::STRING_TO_LANGUAGE = {{"en", EN}, {"bg", BG}, {"ru", RU}, {"pt", PT},
								{"pl", PL}, {"de", DE}, {"jp", JP}, {"mk", MK}};

void L10n::load(const char* __restrict path) {
	if (!enTranslations.IsNull() && strcmp(path, EN_PATH) == 0) {
		translations = std::move(enTranslations);
		return;
	} else if (enTranslations.IsNull()) {
		enTranslations = loadJson(EN_PATH);
	}

	translations = loadJson(path);
}

rapidjson::Document L10n::loadJson(const char* __restrict path) {
	FILE* file = fopen(path, "r");

	rapidjson::Document document;

	char readBuffer[512];
	rapidjson::FileReadStream fileStream(file, readBuffer, sizeof readBuffer);
	document.ParseStream(fileStream);

	fclose(file);

	return document;
}
