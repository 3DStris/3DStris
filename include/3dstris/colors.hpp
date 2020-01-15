#pragma once

#include <3dstris/util.hpp>

constexpr Color WHITE = C2D_Color32(255, 255, 255, 255);
constexpr Color BLACK = C2D_Color32(0, 0, 0, 255);

constexpr Color BOARD = C2D_Color32(10, 10, 10, 255);
constexpr Color GRID = C2D_Color32(1, 1, 1, 100);

constexpr Color BACKGROUND = C2D_Color32(36, 36, 36, 255);

namespace Colors {
	constexpr Color I = C2D_Color32(65, 175, 222, 255);
	constexpr Color O = C2D_Color32(247, 211, 62, 255);
	constexpr Color L = C2D_Color32(239, 149, 53, 255);
	constexpr Color J = C2D_Color32(25, 131, 191, 255);
	constexpr Color S = C2D_Color32(102, 198, 92, 255);
	constexpr Color T = C2D_Color32(180, 81, 172, 255);
	constexpr Color Z = C2D_Color32(239, 98, 77, 255);
	// Ghost piece colors (just lower opacity)
	constexpr Color IGhost = C2D_Color32(65, 175, 222, 100);
	constexpr Color OGhost = C2D_Color32(247, 211, 62, 100);
	constexpr Color LGhost = C2D_Color32(239, 149, 53, 100);
	constexpr Color JGhost = C2D_Color32(25, 131, 191, 100);
	constexpr Color SGhost = C2D_Color32(102, 198, 92, 100);
	constexpr Color TGhost = C2D_Color32(180, 81, 172, 100);
	constexpr Color ZGhost = C2D_Color32(239, 98, 77, 100);
}  // namespace Colors

constexpr std::array<Color, 7> colors{Colors::I, Colors::O, Colors::L,
									  Colors::J, Colors::S, Colors::T,
									  Colors::Z};
constexpr std::array<Color, 7> colorsGhost{
	Colors::IGhost, Colors::OGhost, Colors::LGhost, Colors::JGhost,
	Colors::SGhost, Colors::TGhost, Colors::ZGhost};
