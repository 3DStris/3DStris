#pragma once

#include <3dstris/sprites.h>
#include <3dstris/game.hpp>
#include <3dstris/util.hpp>

constexpr Color WHITE = C2D_Color32(255, 255, 255, 255);
constexpr Color BLACK = C2D_Color32(0, 0, 0, 255);

constexpr Color BOARD = C2D_Color32(10, 10, 10, 255);
constexpr Color GRID = C2D_Color32(1, 1, 1, 100);

constexpr Color BACKGROUND = C2D_Color32(36, 36, 36, 255);

class Textures {
   public:
	const static C2D_Image& get(const size_t index) {
		// man this is some fucking wizardry i don't know why this works but
		// neither do i care
		static Textures textures;

		return textures.all[index];
	}

	static C2D_ImageTint GHOST;

   private:
	const C2D_SpriteSheet spriteSheet;

	std::array<C2D_Image, 7> all;

	Textures();
	~Textures();
};  // namespace Textures
