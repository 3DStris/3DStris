#include <rapidjson/filereadstream.h>
#include <3dstris/config/l10n.hpp>

constexpr std::array<L10n::Language, L10n::LANGUAGE_COUNT> L10n::LANGUAGES;

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
