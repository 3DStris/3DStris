#pragma once

#include <citro2d.h>

#include <array>

using Color = u32;

class Textures final {
   public:
	static const C2D_Image& get(const size_t index) {
		static Textures textures;
		return textures.all[index];
	}

	static Color getColor(const size_t index, const bool ghost = false) {
		static DefaultColors defaultColors;
		return defaultColors.get(index, ghost);
	}

	static C2D_ImageTint GHOST;

   private:
	class DefaultColors {
	   public:
		static const Color& get(const size_t index, const bool ghost = false) {
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
};	// namespace Textures
