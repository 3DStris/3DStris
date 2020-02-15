#include <rapidjson/filereadstream.h>
#include <3dstris/config/l10n.hpp>

const phmap::btree_map<L10n::Language, const char*> L10n::LANGUAGE_TO_STRING = {
	{EN, "en"}, {BG, "bg"}, {RU, "ru"}, {PT, "pt"},
	{PL, "pl"}, {DE, "de"}, {JP, "jp"}, {MK, "mk"}};

const phmap::btree_map<const char*, L10n::Language, L10n::CompareString>
	L10n::STRING_TO_LANGUAGE = {{"en", EN}, {"bg", BG}, {"ru", RU}, {"pt", PT},
								{"pl", PL}, {"de", DE}, {"jp", JP}, {"mk", MK}};

void L10n::load(const char* path) {
	if (!translations.empty()) {
		translations.clear();
	}

	const auto document = loadJson(path);
	const auto& trs = document.GetObject();
	for (const auto& tr : trs) {
		translations[tr.name.GetString()] = tr.value.GetString();
	}

	if (strcmp(path, EN_PATH) != 0) {
		const auto enDocument = loadJson(EN_PATH);
		const auto& enTrs = enDocument.GetObject();

		if (enTrs.MemberCount() != trs.MemberCount()) {
			for (const auto& tr : enTrs) {
				const std::string name = tr.name.GetString();
				if (!translations.count(name)) {
					translations[name] = tr.value.GetString();
				}
			}
		}
	}
}

rapidjson::Document L10n::loadJson(const char* path) {
	FILE* file = fopen(path, "r");

	rapidjson::Document document;

	char readBuffer[512];
	rapidjson::FileReadStream fileStream(file, readBuffer, sizeof readBuffer);
	document.ParseStream(fileStream);

	fclose(file);

	return document;
}
