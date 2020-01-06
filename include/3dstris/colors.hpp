#pragma once

#include <3dstris/util.hpp>

constexpr Color WHITE = C2D_Color32(255, 255, 255, 255);
constexpr Color BLACK = C2D_Color32(0, 0, 0, 255);
constexpr Color GRIDBLACK = C2D_Color32(0, 0, 0, 100);

constexpr Color BUTTON = C2D_Color32(79, 79, 79, 255);
constexpr Color BUTTON_BORDER = C2D_Color32(89, 89, 89, 255);
constexpr Color BUTTON_HELD = C2D_Color32(64, 64, 64, 255);

constexpr Color FIELD = C2D_Color32(94, 94, 94, 255);
constexpr Color FIELD_HELD = C2D_Color32(75, 75, 75, 255);

constexpr Color PANEL = C2D_Color32(60, 60, 60, 255);
constexpr Color PANEL_BORDER = C2D_Color32(88, 88, 88, 255);

constexpr Color PAUSED = C2D_Color32(0, 0, 0, 190);

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
