#include <3dstris/sprites.h>
#include <3dstris/util/colorstextures.hpp>

// i love macros
// name's there for convenience's sake
#define SPRITE(__name, index) \
	C2D_SpriteSheetGetImage(spriteSheet, sprites_##index##_idx)

#define COLOR(__name, ...) C2D_Color32(__VA_ARGS__, 255)

constexpr Color setAlpha(const Color color, const u8 alpha) {
	return (color & 0xff) | (color & 0xff00) | (color & 0xff0000) |
		   (alpha << 24);
}

C2D_ImageTint Textures::GHOST;

Textures::Textures()
	: spriteSheet(C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x")),
	  all({SPRITE(I, cyan), SPRITE(O, yellow), SPRITE(L, orange),
		   SPRITE(J, blue), SPRITE(S, green), SPRITE(T, purple),
		   SPRITE(Z, red)}) {
	C2D_AlphaImageTint(&GHOST, 0.3902f);
}

Textures::~Textures() {
	C2D_SpriteSheetFree(spriteSheet);
}

Textures::DefaultColors::DefaultColors()
	: normal({COLOR(I, 65, 175, 222), COLOR(O, 247, 211, 62),
			  COLOR(L, 239, 149, 53), COLOR(J, 25, 131, 191),
			  COLOR(S, 102, 198, 92), COLOR(T, 180, 81, 172),
			  COLOR(Z, 239, 98, 77)}) {
	for (size_t i = 0; i < normal.size(); i++) {
		ghost[i] = setAlpha(normal[i], 100);
	}
}
