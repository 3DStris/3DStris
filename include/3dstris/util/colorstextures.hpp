#pragma once

#include <citro2d.h>

#include <array>

using Color = u32;

class Textures final {
   public:
	static const C2D_Image& get(size_t index);
	static Color getColor(size_t index, bool ghost = false);

	static C2D_ImageTint GHOST;

   private:
	class DefaultColors {
	   public:
		static const Color& get(size_t index, bool ghost = false);

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
