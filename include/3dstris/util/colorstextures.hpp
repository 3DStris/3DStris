#pragma once

#include <3dstris/util.hpp>

constexpr Color WHITE = C2D_Color32(230, 230, 230, 255);
constexpr Color BLACK = C2D_Color32(0, 0, 0, 255);

constexpr Color BOARD = C2D_Color32(40, 42, 62, 255);
constexpr Color GRID = C2D_Color32(50, 52, 72, 100);

constexpr Color BACKGROUND = C2D_Color32(20, 21, 31, 255);

class Textures {
   public:
	const static C2D_Image& get(const size_t index) {
		// man this is some fucking wizardry i don't know why this works but
		// neither do i care
		static Textures textures;
		return textures.all[index];
	}

	static Color getColor(const size_t index, bool ghost = false) {
		static DefaultColors defaultColors;
		return defaultColors.get(index, ghost);
	}

	static C2D_ImageTint GHOST;

   private:
	class DefaultColors {
	   public:
		friend Textures;

		const static Color& get(const size_t index, bool ghost = false) {
			// man this is some fucking wizardry i don't know why this works but
			// neither do i care
			static DefaultColors defaultTints;

			return ghost ? defaultTints.ghost[index]
						 : defaultTints.normal[index];
		}

		DefaultColors();

	   private:
		std::array<Color, 7> normal;
		std::array<Color, 7> ghost;
	};

	const C2D_SpriteSheet spriteSheet;

	std::array<C2D_Image, 7> all;

	Textures();
	~Textures();
};  // namespace Textures
