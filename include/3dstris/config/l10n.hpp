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

	enum Language { EN, BG, RU, PT, PL, DE, JP, MK };

	const static std::array<char[2 + 1], 8> LANGUAGE_TO_STRING;
	const static phmap::btree_map<const char*, Language, CompareString>
		STRING_TO_LANGUAGE;

	static const char* languageToString(const Language language) {
		return static_cast<u8>(language) < LANGUAGE_TO_STRING.size()
				   ? LANGUAGE_TO_STRING.at(language)
				   : "en";
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
			{EN, images_us_idx}, {BG, images_bg_idx}, {RU, images_ru_idx},
			{PT, images_br_idx}, {PL, images_pl_idx}, {DE, images_de_idx},
			{JP, images_jp_idx}, {MK, images_mk_idx}};

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
