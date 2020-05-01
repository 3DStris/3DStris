#pragma once

#include <parallel_hashmap/btree.h>
#include <parallel_hashmap/phmap.h>
#include <sajson.h>

#include <3dstris/util/hash.hpp>
#include <3dstris/util/string.hpp>

class L10n final {
   public:
	using Language = String;
	using LanguageCodes = phmap::btree_set<String>;

	static constexpr StringView EN_US = "en_US";

	static LanguageCodes getCodes();

	void loadLanguage(const Language& language) noexcept;
	void load(const char* __restrict path, const Language& language) noexcept;

	String get(StringView key) const noexcept;

	static size_t getFlag(const Language& language) noexcept;

   private:
	using Translations =
		phmap::flat_hash_map<String, String, StringHash, StringEq>;

	static constexpr const char* EN_US_PATH = "romfs:/lang/en_US.json";

	void loadFromJson(const char* __restrict path, const StringView language,
					  Translations& where) noexcept;

	static char* getPath(const Language& language,
						 char* __restrict buf) noexcept;

	Translations translations;
	Translations enTranslations;
};
