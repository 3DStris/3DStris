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
	enum Language { EN, BG, RU, PT, PL, DE, JP, MK, FR };
	static constexpr std::array<Language, LANGUAGE_COUNT> LANGUAGES{
		EN, BG, RU, PT, PL, DE, JP, MK, FR};

	static const char* languageToString(const Language language) {
		static constexpr std::array<char[2 + 1], LANGUAGE_COUNT>
			LANGUAGE_TO_STRING = {"en", "bg", "ru", "pt", "pl",
								  "de", "jp", "mk", "fr"};

		return static_cast<u8>(language) < LANGUAGE_TO_STRING.size()
				   ? LANGUAGE_TO_STRING[language]
				   : LANGUAGE_TO_STRING.front();
	}
	static Language stringToLanguage(const char* language) {
		const static phmap::btree_map<const char*, Language, CompareString>
			STRING_TO_LANGUAGE = {{"en", EN}, {"bg", BG}, {"ru", RU},
								  {"pt", PT}, {"pl", PL}, {"de", DE},
								  {"jp", JP}, {"mk", MK}, {"fr", FR}};

		try {
			return STRING_TO_LANGUAGE.at(language);
		} catch (...) {
			return EN;
		}
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

	rapidjson::Document loadJson(const char* path);

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

	static char* getPath(const Language language, char* buf) {
		constexpr auto FORMAT_STRING = "romfs:/lang/%s.json";
		if (language == EN) {
			strcpy(buf, EN_PATH);
			return buf;
		}

		sprintf(buf, FORMAT_STRING, languageToString(language));
		return buf;
	}

	static size_t getFlag(const Language language) {
		static constexpr std::array<size_t, LANGUAGE_COUNT> LANGUAGE_TO_ICON{
			images_us_idx, images_bg_idx, images_ru_idx,
			images_br_idx, images_pl_idx, images_de_idx,
			images_jp_idx, images_mk_idx, images_fr_idx};

		return static_cast<u8>(language) < LANGUAGES.size()
				   ? LANGUAGE_TO_ICON[language]
				   : LANGUAGE_TO_ICON.front();
	}

   private:
	static constexpr auto EN_PATH = "romfs:/lang/en.json";

	rapidjson::Document enTranslations;
	rapidjson::Document translations;
};
