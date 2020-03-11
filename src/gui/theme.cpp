#include <3dstris/gui/theme.hpp>
#include <3dstris/util/log.hpp>

#define MEMBER(name)                                      \
	if (json.HasMember(#name) && json[#name].IsString())  \
		name = fromString(#name, json[#name].GetString(), \
						  json[#name].GetStringLength()); \
	else                                                  \
		LOG_WARN("Invalid theme member" #name)

void Theme::parse(const rapidjson::Document& json) {
	// TODO: checks
	format.id = sdsnew(json["id"].GetString());
	format.name = sdsnew(json["name"].GetString());

	static const auto fromString = [](const char* name, const char* str,
									  const size_t len) -> Color {
		char* end;
		const u32 color = strtoul(str, &end, 16);
		if (end[0] == '\0' && errno == 0) {
			if (len == 10) {  // 0xAARRGGBB
				const u8 a = (color >> 24) & 0xff;
				const u8 r = (color >> 16) & 0xff;
				const u8 g = (color >> 8) & 0xff;
				const u8 b = color & 0xff;
				return C2D_Color32(r, g, b, a);
			} else if (len == 8) {	// 0xRRGGBB
				const u8 r = (color >> 16) & 0xff;
				const u8 g = (color >> 8) & 0xff;
				const u8 b = color & 0xff;
				return C2D_Color32(r, g, b, 255);
			}
		}
		LOG_WARN("Invalid theme member %s (with value %s); using black", name,
				 str);
		return Theme::BLACK;
	};

	MEMBER(background);
	MEMBER(text);

	MEMBER(button);
	MEMBER(buttonHeld);
	MEMBER(buttonOutline);

	MEMBER(inputField);
	MEMBER(inputFieldHeld);

	MEMBER(panel);
	MEMBER(panelOutline);

	MEMBER(board);
	MEMBER(grid);
}
