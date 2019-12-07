#pragma once

#include <3dstris/util.hpp>

const Color WHITE = C2D_Color32(255, 255, 255, 255);
const Color BLACK = C2D_Color32(0, 0, 0, 255);
const Color GRIDBLACK = C2D_Color32(0, 0, 0, 100);

namespace Colors {
	const Color I = C2D_Color32(65, 175, 222, 255);
	const Color O = C2D_Color32(247, 211, 62, 255);
	const Color L = C2D_Color32(239, 149, 53, 255);
	const Color J = C2D_Color32(25, 131, 191, 255);
	const Color S = C2D_Color32(102, 198, 92, 255);
	const Color T = C2D_Color32(180, 81, 172, 255);
	const Color Z = C2D_Color32(239, 98, 77, 255);
	// Ghost piece colors (just lower opacity)
	const Color IGhost = C2D_Color32(65, 175, 222, 100);
	const Color OGhost = C2D_Color32(247, 211, 62, 100);
	const Color LGhost = C2D_Color32(239, 149, 53, 100);
	const Color JGhost = C2D_Color32(25, 131, 191, 100);
	const Color SGhost = C2D_Color32(102, 198, 92, 100);
	const Color TGhost = C2D_Color32(180, 81, 172, 100);
	const Color ZGhost = C2D_Color32(239, 98, 77, 100);
}  // namespace Colors

const std::array<Color, 7> colors{Colors::I, Colors::O, Colors::L, Colors::J,
								  Colors::S, Colors::T, Colors::Z};
const std::array<Color, 7> colorsGhost{
	Colors::IGhost, Colors::OGhost, Colors::LGhost, Colors::JGhost,
	Colors::SGhost, Colors::TGhost, Colors::ZGhost};
