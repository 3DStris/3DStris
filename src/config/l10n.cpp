#include <3dstris/images.h>
#include <rapidjson/filereadstream.h>

#include <3dstris/config/l10n.hpp>
#include <3dstris/util/string.hpp>

#define FLAG(lang) images_##lang##_idx

constexpr std::array<L10n::Language, L10n::LANGUAGE_COUNT> L10n::LANGUAGES;

void L10n::load(const char* __restrict path) noexcept {
	if (enTranslations.IsNull()) {
		enTranslations = loadJson(EN_PATH);
	}

	if (strcmp(path, EN_PATH) == 0) {
		translations = std::move(enTranslations);
		return;
	}

	translations = loadJson(path);
}

rapidjson::Document L10n::loadJson(const char* __restrict path) noexcept {
	FILE* file = fopen(path, "r");

	if (!file && strcmp(path, EN_PATH) != 0) {
		LOG_ERROR("Failed to load language JSON, falling back to English...");
		loadJson(EN_PATH);
	} else if (!file) {
		LOG_FATAL(
			"Failed to load English JSON, something's gone horribly wrong");
		std::exit(1);
	}

	rapidjson::Document document;

	char readBuffer[512];
	rapidjson::FileReadStream fileStream(file, readBuffer, sizeof readBuffer);
	document.ParseStream(fileStream);

	fclose(file);

	return document;
}

String L10n::get(const char* __restrict key) const noexcept {
	if (translations.HasMember(key)) {
		return translations[key].GetString();
	} else if (!enTranslations.IsNull()) {
		if (enTranslations.HasMember(key)) {
			return enTranslations[key].GetString();
		}
	}

	return key;
}

size_t L10n::getFlag(const Language language) noexcept {
	assert(static_cast<u8>(language) < LANGUAGE_COUNT);

	static constexpr std::array<size_t, LANGUAGE_COUNT> LANGUAGE_TO_ICON{
		FLAG(us), FLAG(bg), FLAG(ru), FLAG(br), FLAG(pl),
		FLAG(de), FLAG(jp), FLAG(mk), FLAG(fr)};

	return static_cast<u8>(language) < LANGUAGE_COUNT
			   ? LANGUAGE_TO_ICON[static_cast<size_t>(language)]
			   : images_un_idx;
}

char* L10n::getPath(Language language, char* __restrict buf) noexcept {
	constexpr auto FORMAT_STRING = "romfs:/lang/%s.json";
	if (language == Language::EN) {
		strcpy(buf, EN_PATH);
		return buf;
	}

	sprintf(buf, FORMAT_STRING, languageToString(language));
	return buf;
}
