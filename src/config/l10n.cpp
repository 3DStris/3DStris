extern "C" {
#include <3ds/romfs.h>
#include <3ds/services/fs.h>
#include <3ds/util/utf.h>
}

#include <3dstris/images.h>
#include <dirent.h>
#include <sajson.h>

#include <3dstris/config/l10n.hpp>
#include <3dstris/util/log.hpp>

#define FLAG(lang) \
	{ #lang, images_##lang##_idx }

L10n::LanguageCodes L10n::getCodes() {
	const auto sdsEqStr = [](sds lhs, const char* __restrict rhs) {
		const size_t len1 = sdslen(lhs);
		const size_t len2 = strlen(rhs);
		if (len1 != len2) {
			return false;
		}
		return memcmp(lhs, rhs, (len1 < len2) ? len1 : len2) == 0;
	};

	DIR* dp = opendir("romfs:/lang/");
	if (!dp) {
		LOG_FATAL(
			"Failed to open translation directory! Is the ROMFS messed "
			"up?");
		std::exit(1);
	}

	L10n::LanguageCodes entries;

	dirent* ep;
	while ((ep = readdir(dp))) {
		if (ep->d_name[0] == '.') {
			continue;
		}

		s32 count;
		sds* split =
			sdssplitlen(ep->d_name, strlen(ep->d_name), ".", 1, &count);
		if (!count) {
			LOG_WARN("Found file without extension in translation directory");
		}

		if (split) {
			if (sdsEqStr(split[count - 1], "json")) {
				entries.insert(split[0]);
			} else {
				LOG_WARN("Found non-JSON file in translation directory");
			}

			for (s32 i = 1; i < count; ++i) {
				sdsfree(split[i]);
			}
			delete split;
		} else {
			LOG_ERROR("Failed to split filename");
		}
	}
	closedir(dp);

	return entries;
}

void L10n::loadLanguage(const Language& language) noexcept {
	constexpr auto FORMAT_STRING_LEN =
		22;	 // I didn't feel like adding a constexpr
			 // strlen() method just for this.

	LOG_INFO("Loading language %s", language.s);
	char buf[FORMAT_STRING_LEN + 1];
	load(getPath(language, buf), language);
	LOG_INFO("Loaded language");
}

void L10n::load(const char* __restrict path,
				const Language& language) noexcept {
	if (enTranslations.empty()) {
		LOG_DEBUG("Loading en_US as fallback");
		loadFromJson(EN_US_PATH, EN_US, enTranslations);
	}

	if (language == EN_US) {
		translations = std::move(enTranslations);
		return;
	}

	translations.clear();
	loadFromJson(path, language, translations);
}

#define FALLBACK(condition, reason, ...)                         \
	if (condition && language != EN_US) {                        \
		LOG_ERROR("Failed to deserialize language JSON: " reason \
				  "\nFalling back to English...",                \
				  ##__VA_ARGS__);                                \
		return loadFromJson(EN_US_PATH, EN_US, where);           \
	} else if (condition) {                                      \
		LOG_FATAL("Failed to deserialize English JSON: " reason, \
				  ##__VA_ARGS__);                                \
		std::exit(1);                                            \
	}
void L10n::loadFromJson(const char* __restrict path, const StringView language,
						Translations& where) noexcept {
	FILE* fp = fopen(path, "r");

	if (!fp && language != EN_US) {
		LOG_ERROR(
			"Failed to load language JSON into memory, falling back to "
			"English...");
		return loadFromJson(EN_US_PATH, EN_US, where);
	} else if (!fp) {
		LOG_FATAL(
			"Failed to load English JSON into memory, something's gone "
			"horribly wrong");
		std::exit(1);
	}

	fseek(fp, 0, SEEK_END);
	size_t fsize = static_cast<size_t>(ftell(fp));
	FALLBACK(fsize == 0, "File is empty")
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
		const auto key = root.get_object_key(i);
		const auto value = root.get_object_value(i);

		FALLBACK(value.get_type() != sajson::TYPE_STRING,
				 "Value of key \"%s\" must be of type string", key.data())
		if (value.get_string_length() != 0) {
			where[String(key.data(), key.length())] =
				String(value.as_cstring(), value.get_string_length());
		} else {
			LOG_DEBUG(
				"Empty translation for key \"%s\"; probably Weblate's fault",
				key.data());
		}
	}
	delete[] buffer;
}

String L10n::get(const StringView key) const noexcept {
	const auto it = translations.find(key);
	if (it != translations.end()) {
		return it->second;
	}

	if (!enTranslations.empty()) {
		const auto enIt = enTranslations.find(key);
		if (enIt != enTranslations.end()) {
			LOG_DEBUG(
				"Translation for key \"%s\" missing, using English "
				"translation instead",
				key.data());
			return enIt->second;
		}
	}

	LOG_DEBUG("Translation for key \"%s\" missing", key.data());
	return String(key);
}

size_t L10n::getFlag(const Language& language) noexcept {
	static const phmap::flat_hash_map<StringView, size_t, StringHash, StringEq>
		FLAGS{FLAG(en_US), FLAG(bg_BG), FLAG(ru_RU), FLAG(pt_BR),
			  FLAG(pl_PL), FLAG(de_DE), FLAG(ja_JP), FLAG(mk_MK),
			  FLAG(fr_FR), FLAG(da_DK), FLAG(nb_NO), FLAG(id_ID)};

	const auto flag = FLAGS.find(language);
	return flag != FLAGS.end() ? flag->second : images_un_idx;
}

char* L10n::getPath(const Language& language, char* __restrict buf) noexcept {
	if (language == EN_US) {
		strcpy(buf, EN_US_PATH);
		return buf;
	}

	sprintf(buf, "romfs:/lang/%s.json", language.s);
	return buf;
}

constexpr StringView L10n::EN_US;
constexpr const char* L10n::EN_US_PATH;
