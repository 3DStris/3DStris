#pragma once

#include <assert.h>
#include <robin_hood.h>
#include <sajson.h>
#include <sds.h>

#include <3dstris/util/hash.hpp>
#include <3dstris/util/log.hpp>
#include <3dstris/util/string.hpp>
#include <array>

class L10n final {
   public:
	static constexpr size_t LANGUAGE_COUNT = 10;

	enum class Language { EN, BG, RU, PT, PL, DE, JP, MK, FR, DA };
	static constexpr std::array<Language, LANGUAGE_COUNT> LANGUAGES{
		Language::EN, Language::BG, Language::RU, Language::PT, Language::PL,
		Language::DE, Language::JP, Language::MK, Language::FR, Language::DA};

	static StringLiteral languageToString(const Language language) noexcept {
		assert(static_cast<size_t>(language) < LANGUAGE_COUNT);

		static constexpr std::array<StringLiteral, LANGUAGE_COUNT>
			LANGUAGE_TO_STRING{"en", "bg", "ru", "pt", "pl",
							   "de", "jp", "mk", "fr", "da"};

		return LANGUAGE_TO_STRING[static_cast<size_t>(language)];
	}

	void loadLanguage(const Language language) noexcept {
		constexpr auto FORMAT_STRING_LEN =
			19;	 // I didn't feel like adding a constexpr
				 // strlen() method just for this.

		LOG_INFO("Loading language %s", languageToString(language).data());
		char buf[FORMAT_STRING_LEN + 1];
		load(getPath(language, buf), language);
		LOG_INFO("Loaded language");
	}
	void load(const char* __restrict path, Language language) noexcept;

	template <typename StringType>
	String get(const StringType& key) const noexcept {
		if (translations.contains(key)) {
			return translations.at(key);
		} else if (!enTranslations.empty()) {
			if (enTranslations.contains(key)) {
				LOG_DEBUG(
					"Translation for key \"%s\" missing, using English "
					"translation instead",
					key);
				return enTranslations.at(key);
			}
		}

		return key;
	}

	static size_t getFlag(Language language) noexcept;

   private:
	using Translations =
		robin_hood::unordered_node_map<String, String, Hash<String>>;

	static constexpr auto EN_PATH = "romfs:/lang/en.json";

	void loadFromJson(const char* __restrict path, const Language language,
					  Translations& where) noexcept;

	static char* getPath(const Language language,
						 char* __restrict buf) noexcept;

	Translations enTranslations;
	Translations translations;
};
