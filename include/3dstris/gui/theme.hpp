#pragma once

extern "C" {
#include <c2d/base.h>
}
#include <rapidjson/document.h>
#include <sds.h>

using Color = uint32_t;

struct Theme final {
	static constexpr Color WHITE = C2D_Color32(255, 255, 255, 255);
	static constexpr Color BLACK = C2D_Color32(0, 0, 0, 255);

	Theme(sds id, sds name) : format(id, name) {}
	Theme(const rapidjson::Document& json) { parse(json); }

	struct Format {
		Format() : id(sdsempty()), name(sdsempty()) {}
		Format(sds id, sds name) : id(id), name(name) {}

		Format(Format&& other) : Format(other.id, other.name) {
			other.id = nullptr;
			other.name = nullptr;
		}

		~Format() {
			sdsfree(id);
			sdsfree(name);
		}
		void operator=(const Format& other) {
			sdsfree(id);
			sdsfree(name);

			id = sdsdup(other.id);
			name = sdsdup(other.name);
		}
		void operator=(Format&& other) {
			sdsfree(id);
			sdsfree(name);

			id = other.id;
			name = other.name;

			other.id = nullptr;
			other.name = nullptr;
		}

		sds id;
		sds name;
	} format;

	Color background;
	Color text;

	Color button;
	Color buttonOutline;
	Color buttonHeld;

	Color inputField;
	Color inputFieldHeld;

	Color panel;
	Color panelOutline;

	Color board;
	Color grid;

	void parse(const rapidjson::Document& json);

	static Theme night() {
		static constexpr auto id = "night";
		static constexpr auto name = "Night";

		Theme night(sdsnewlen(id, 5), sdsnewlen(name, 5));
		night.background = C2D_Color32(20, 21, 31, 255);
		night.text = C2D_Color32(230, 230, 230, 255);

		night.button = C2D_Color32(33, 34, 48, 255);
		night.buttonOutline = C2D_Color32(35, 36, 51, 255);
		night.buttonHeld = C2D_Color32(26, 27, 38, 255);

		night.inputField = C2D_Color32(30, 32, 47, 255);
		night.inputFieldHeld = C2D_Color32(28, 30, 44, 255);

		night.panel = C2D_Color32(35, 37, 55, 255);
		night.panelOutline = C2D_Color32(37, 39, 58, 255);

		night.board = C2D_Color32(40, 42, 62, 255);
		night.grid = C2D_Color32(50, 52, 72, 100);

		return night;
	}
};
