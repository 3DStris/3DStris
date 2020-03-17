#pragma once

#include <parallel_hashmap/phmap.h>
#include <rapidjson/document.h>
#include <sds.h>

#include <3dstris/util/log.hpp>

class L10n final {
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

	static const char* languageToString(const Language language) noexcept {
		assert(static_cast<u8>(language) < LANGUAGE_COUNT);

		static constexpr std::array<char[2 + 1], LANGUAGE_COUNT>
			LANGUAGE_TO_STRING = {"en", "bg", "ru", "pt", "pl",
								  "de", "jp", "mk", "fr"};

		return LANGUAGE_TO_STRING[static_cast<size_t>(language)];
	}

	void loadLanguage(const Language language) noexcept {
		constexpr auto FORMAT_STRING_LEN =
			19;	 // I didn't feel like adding a constexpr strlen() method just
				 // for this.

		LOG_INFO("Loading language %s", languageToString(language));
		char buf[FORMAT_STRING_LEN + 1];
		load(getPath(language, buf));
		LOG_INFO("Loaded language");
	}
	void load(const char* __restrict path) noexcept;
	rapidjson::Document loadJson(const char* __restrict path) noexcept;

	sds get(const char* __restrict key) const noexcept;

	static size_t getFlag(Language language) noexcept;

   private:
	static constexpr auto EN_PATH = "romfs:/lang/en.json";

	static char* getPath(const Language language,
						 char* __restrict buf) noexcept;

	rapidjson::Document enTranslations;
	rapidjson::Document translations;
};
