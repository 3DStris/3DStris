#include <3dstris/util/l10n.hpp>

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

	const auto document = loadJson(path).GetObject();

	for (const auto& tr : document) {
		translations[tr.name.GetString()] = tr.value.GetString();
	}

	if (strcmp(path, EN_PATH) != 0) {
		const auto enDocument = loadJson(EN_PATH).GetObject();
		if (enDocument.MemberCount() != document.MemberCount()) {
			for (const auto& tr : enDocument) {
				const auto name = tr.name.GetString();
				if (!translations.count(name)) {
					translations[name] = tr.value.GetString();
				}
			}
		}
	}
}

rapidjson::Document L10n::loadJson(const char* path) {
	FILE* file = fopen(path, "r");

	fseek(file, 0, SEEK_END);
	const size_t length = ftell(file);
	rewind(file);

	sds content = sdsnewlen("", length);
	fread(content, sizeof(char), length, file);
	fclose(file);

	rapidjson::Document document;
	document.Parse(content);
	sdsfree(content);

	return document;
}
