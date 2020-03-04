#pragma once

#include <3dstris/images.h>
#include <parallel_hashmap/btree.h>
#include <rapidjson/document.h>
#include <sds.h>
#include <3dstris/util/log.hpp>

class L10n {
   public:
	struct CompareString {
		bool operator()(const char* a, const char* b) const {
			return strcmp(a, b) < 0;
		}
	};

	static constexpr u8 LANGUAGE_COUNT = 9;
	enum class Language { EN, BG, RU, PT, PL, DE, JP, MK, FR };
	static constexpr std::array<Language, LANGUAGE_COUNT> LANGUAGES{
		Language::EN, Language::BG, Language::RU, Language::PT, Language::PL,
		Language::DE, Language::JP, Language::MK, Language::FR};

	static const char* languageToString(const Language language) {
		assert(static_cast<u8>(language) < LANGUAGE_COUNT);

		static constexpr std::array<char[2 + 1], LANGUAGE_COUNT>
			LANGUAGE_TO_STRING = {"en", "bg", "ru", "pt", "pl",
								  "de", "jp", "mk", "fr"};

		return LANGUAGE_TO_STRING[static_cast<size_t>(language)];
	}
	static Language stringToLanguage(const char* __restrict language) {
		const static phmap::btree_map<const char*, Language, CompareString>
			STRING_TO_LANGUAGE = {{"en", Language::EN}, {"bg", Language::BG},
								  {"ru", Language::RU}, {"pt", Language::PT},
								  {"pl", Language::PL}, {"de", Language::DE},
								  {"jp", Language::JP}, {"mk", Language::MK},
								  {"fr", Language::FR}};

		assert(STRING_TO_LANGUAGE.contains(language));

		return STRING_TO_LANGUAGE.at(language);
	}

	void loadLanguage(const Language language) {
		constexpr auto FORMAT_STRING_LEN =
			19;  // I didn't feel like adding a constexpr strlen() method just
				 // for this.

		LOG_INFO("Loading language %s", languageToString(language));
		char buf[FORMAT_STRING_LEN + 1];
		load(getPath(language, buf));
		LOG_INFO("Loaded language");
	}
	void load(const char* __restrict path);

	rapidjson::Document loadJson(const char* __restrict path);

	sds get(const char* __restrict key) const {
		if (translations.HasMember(key)) {
			return sdsnew(translations[key].GetString());
		} else if (!enTranslations.IsNull()) {
			if (enTranslations.HasMember(key)) {
				return sdsnew(enTranslations[key].GetString());
			}
		}

		return sdsnew(key);
	}

	static char* getPath(const Language language, char* __restrict buf) {
		constexpr auto FORMAT_STRING = "romfs:/lang/%s.json";
		if (language == Language::EN) {
			strcpy(buf, EN_PATH);
			return buf;
		}

		sprintf(buf, FORMAT_STRING, languageToString(language));
		return buf;
	}

	static size_t getFlag(const Language language) {
		assert(static_cast<u8>(language) < LANGUAGE_COUNT);

		static constexpr std::array<size_t, LANGUAGE_COUNT> LANGUAGE_TO_ICON{
			images_us_idx, images_bg_idx, images_ru_idx,
			images_br_idx, images_pl_idx, images_de_idx,
			images_jp_idx, images_mk_idx, images_fr_idx};

		return static_cast<u8>(language) < LANGUAGE_COUNT
				   ? LANGUAGE_TO_ICON[static_cast<size_t>(language)]
				   : images_un_idx;
	}

   private:
	static constexpr auto EN_PATH = "romfs:/lang/en.json";

	rapidjson::Document enTranslations;
	rapidjson::Document translations;
};
