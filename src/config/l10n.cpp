#include <3dstris/images.h>
#include <sajson.h>

#include <3dstris/config/l10n.hpp>

#define FLAG(lang) images_##lang##_idx

constexpr std::array<L10n::Language, L10n::LANGUAGE_COUNT> L10n::LANGUAGES;

void L10n::load(const char* __restrict path,
				const L10n::Language language) noexcept {
	if (enTranslations.empty()) {
		loadFromJson(EN_PATH, language, enTranslations);
	}

	if (language == Language::EN) {
		translations = std::move(enTranslations);
		return;
	}

	translations.clear();
	loadFromJson(path, language, translations);
}

#define FALLBACK(condition, reason, ...)                         \
	if (condition && language != Language::EN) {                 \
		LOG_ERROR("Failed to deserialize language JSON: " reason \
				  " Falling back to English...",                 \
				  ##__VA_ARGS__);                                \
		return loadFromJson(EN_PATH, Language::EN, where);       \
	} else if (condition) {                                      \
		LOG_FATAL("Failed to deserialize English JSON: " reason, \
				  ##__VA_ARGS__);                                \
		std::exit(1);                                            \
	}
void L10n::loadFromJson(const char* __restrict path,
						const L10n::Language language,
						Translations& where) noexcept {
	FILE* fp = fopen(path, "r");

	if (!fp && language != Language::EN) {
		LOG_ERROR(
			"Failed to load language JSON into memory, falling back to "
			"English...");
		return loadFromJson(EN_PATH, language, where);
	} else if (!fp) {
		LOG_FATAL(
			"Failed to load English JSON into memory, something's gone "
			"horribly wrong");
		std::exit(1);
	}

	fseek(fp, 0, SEEK_END);
	size_t fsize = static_cast<size_t>(ftell(fp));
	rewind(fp);

	char* buffer = new char[fsize];
	fread(buffer, sizeof(char), fsize, fp);
	fclose(fp);

	const sajson::document json =
		sajson::parse(sajson::dynamic_allocation(),
					  sajson::mutable_string_view(fsize, buffer));

	FALLBACK(!json.is_valid(), "%s at %u:%u", json.get_error_line(),
			 json.get_error_column(), json.get_error_message_as_cstring())

	const auto& root = json.get_root();
	FALLBACK(root.get_type() != sajson::TYPE_OBJECT, "Root type is not object")

	LOG_DEBUG("Loading %u translations", root.get_length());
	for (size_t i = 0; i < root.get_length(); ++i) {
		const auto& key = root.get_object_key(i);
		const auto value = root.get_object_value(i);

		FALLBACK(value.get_type() != sajson::TYPE_STRING,
				 "Value of key \"%s\" must be of type string", key.data())
		where[String(key.data(), key.length())] =
			String(value.as_cstring(), value.get_string_length());
	}

	delete[] buffer;
}

size_t L10n::getFlag(const Language language) noexcept {
	assert(static_cast<size_t>(language) < LANGUAGE_COUNT);

	static constexpr std::array<size_t, LANGUAGE_COUNT> LANGUAGE_TO_ICON{
		FLAG(us), FLAG(bg), FLAG(ru), FLAG(br), FLAG(pl),
		FLAG(de), FLAG(jp), FLAG(mk), FLAG(fr), FLAG(da)};

	return static_cast<size_t>(language) < LANGUAGE_COUNT
			   ? LANGUAGE_TO_ICON[static_cast<size_t>(language)]
			   : images_un_idx;
}

char* L10n::getPath(Language language, char* __restrict buf) noexcept {
	constexpr auto FORMAT_STRING = "romfs:/lang/%s.json";
	if (language == Language::EN) {
		strcpy(buf, EN_PATH);
		return buf;
	}

	sprintf(buf, FORMAT_STRING, languageToString(language).data());
	return buf;
}
