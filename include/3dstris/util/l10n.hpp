#pragma once

#include <3dstris/sprites.h>
#include <parallel_hashmap/btree.h>
#include <parallel_hashmap/phmap.h>
#include <rapidjson/document.h>
#include <sds.h>

class L10n {
   public:
	struct CompareString {
		bool operator()(const char* a, const char* b) const {
			return strcmp(a, b) < 0;
		}
	};

	enum Language { EN, BG, RU, PT, PL, DE, JP };

	const static phmap::btree_map<Language, const char*> LANGUAGE_TO_STRING;
	const static phmap::btree_map<const char*, Language, CompareString>
		STRING_TO_LANGUAGE;

	static const char* languageToString(const Language language) {
		try {
			return LANGUAGE_TO_STRING.at(language);
		} catch (...) {
			return "en";
		}
	}
	static Language stringToLanguage(const char* language) {
		try {
			return STRING_TO_LANGUAGE.at(language);
		} catch (...) {
			return EN;
		}
	}

	void loadLanguage(const Language language) {
		sds path = getPath(language);
		load(path);
		sdsfree(path);
	}
	void load(const char* path);

	rapidjson::Document loadJson(const char* path);

	sds get(const char* key) const {
		if (translations.count(key)) {
			return sdsnew(translations.at(key).c_str());
		}

		return sdsnew(key);
	}

	static sds getPath(const Language language) {
		return sdscatfmt(sdsempty(), "romfs:/lang/%s.json",
						 languageToString(language));
	}

	static size_t getFlag(const Language language) {
		static const phmap::flat_hash_map<Language, size_t> LANGUAGE_TO_ICON{
			{EN, sprites_us_idx}, {BG, sprites_bg_idx}, {RU, sprites_ru_idx},
			{PT, sprites_br_idx}, {PL, sprites_pl_idx}, {DE, sprites_de_idx},
			{JP, sprites_jp_idx}};

		return LANGUAGE_TO_ICON.at(language);
	}

   private:
	static constexpr auto EN_PATH = "romfs:/lang/en.json";

	phmap::btree_map<std::string,
					 std::string>
		translations;  // oh dear c++ gods, please forgive me, for
					   // i have used std::string... (okay but
					   // honestly, trying to use char pointers
					   // with this isn't fun)
};
