#pragma once

#include <3dstris/images.h>
#include <parallel_hashmap/btree.h>
#include <parallel_hashmap/phmap.h>
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

	const static std::array<char[2 + 1], LANGUAGE_COUNT> LANGUAGE_TO_STRING;
	const static phmap::btree_map<const char*, Language, CompareString>
		STRING_TO_LANGUAGE;

	static const char* languageToString(const Language language) {
		return static_cast<u8>(language) < LANGUAGE_TO_STRING.size()
				   ? LANGUAGE_TO_STRING[language]
				   : LANGUAGE_TO_STRING.front();
	}
	static Language stringToLanguage(const char* language) {
		try {
			return STRING_TO_LANGUAGE.at(language);
		} catch (...) {
			return EN;
		}
	}

	void loadLanguage(const Language language) {
		LOG_INFO("Loading language %s", languageToString(language));
		sds path = getPath(language);
		load(path);
		sdsfree(path);
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

	static sds getPath(const Language language) {
		return language == Language::EN
				   ? sdsnew(EN_PATH)
				   : sdscatfmt(sdsempty(), "romfs:/lang/%s.json",
							   languageToString(language));
	}

	static size_t getFlag(const Language language) {
		static const std::array<size_t, LANGUAGE_COUNT> LANGUAGE_TO_ICON{
			images_us_idx, images_bg_idx, images_ru_idx,
			images_br_idx, images_pl_idx, images_de_idx,
			images_jp_idx, images_mk_idx, images_fr_idx};

		return static_cast<u8>(language) < LANGUAGE_TO_STRING.size()
				   ? LANGUAGE_TO_ICON[language]
				   : LANGUAGE_TO_ICON.front();
	}

   private:
	static constexpr auto EN_PATH = "romfs:/lang/en.json";

	rapidjson::Document enTranslations;
	rapidjson::Document translations;
};
