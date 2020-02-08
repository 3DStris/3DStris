#include <3dstris/colors.hpp>

// i love macros
// name's there for convenience's sake
#define SPRITE(__name, index) \
	C2D_SpriteSheetGetImage(spriteSheet, sprites_##index##_idx)

C2D_ImageTint Textures::GHOST;

Textures::Textures()
	: spriteSheet(C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x")),
	  all({SPRITE(I, cyan), SPRITE(O, yellow), SPRITE(L, orange),
		   SPRITE(J, blue), SPRITE(S, green), SPRITE(T, purple),
		   SPRITE(Z, red)}) {
	C2D_AlphaImageTint(&GHOST, 0.4f);
}

Textures::~Textures() {
	C2D_SpriteSheetFree(spriteSheet);
}
