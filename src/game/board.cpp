#include <3dstris/game.hpp>
#include <3dstris/game/board.hpp>
#include <3dstris/gui.hpp>
#include <3dstris/util/colorstextures.hpp>
#include <3dstris/util/text.hpp>

Board::Board(const u32 width, const u32 height)
	: width(width), height(height), grid(width * height) {}

void Board::reset() {
	grid.assign(width * height, PieceType::NONE);

	score = 0;
	lastWasTSpin = false;
	comboCount = 0;

	_linesCleared = 0;
	_droppedPieces = 0;
}

void Board::draw(const Pos origin, const u32 tileSize, const float outerThick,
				 const float gridThick) const {
	const Theme& theme = Game::get().getTheme();

	Text scoreText(String::fromFmt("Score: %u", score));
	scoreText.draw();

	GUI::drawOutline(Pos{origin.x, origin.y},
					 WH(width * tileSize, height * tileSize), outerThick,
					 theme.board, 0.1f);

	for (u32 y = 0; y < height; ++y) {
		GUI::drawHLine(Pos{origin.x, origin.y + y * tileSize}, width * tileSize,
					   gridThick, theme.grid, 0);
	}
	for (u32 x = 0; x < width; ++x) {
		GUI::drawVLine(Pos{origin.x + x * tileSize, origin.y},
					   height * tileSize, gridThick, theme.grid, 0);
	}

	for (u32 y = 0; y < height; ++y) {
		for (u32 x = 0; x < width; ++x) {
			const PieceType p = get(x, y);

			if (p != PieceType::NONE && p != PieceType::INVALID) {
				const float pieceX = origin.x + x * tileSize;
				const float pieceY = origin.y + y * tileSize;
				if (Game::get().getConfig().useTextures) {
					C2D_DrawImageAt(Textures::get(static_cast<size_t>(p)),
									pieceX, pieceY, 0.5f);
				} else {
					C2D_DrawRectSolid(
						pieceX, pieceY, 0.5f, tileSize, tileSize,
						Textures::getColor(static_cast<size_t>(p)));
				}
			}
		}
	}
}

void Board::clearLines() noexcept {
	u8 linesCleared = 0;
	for (u32 y = 0; y < height; ++y) {
		bool line = true;
		for (u32 x = 0; x < width; ++x) {
			if (get(x, y) == PieceType::NONE) {
				line = false;
				break;
			}
		}

		if (line) {
			++linesCleared;
			++_linesCleared;
			for (u32 curY = y; curY >= 1; --curY) {
				for (u32 x = 0; x < width; ++x) {
					set(x, curY,
						curY == 1 ? PieceType::NONE : get(x, curY - 1));
				}
			}
		}
	}

	if (linesCleared > 0) {
		++comboCount;
		if (lastWasTSpin) {
			for (u8 i = 0; i < linesCleared; ++i) {
				// A T-spin without a line clear gives 400 score
				score += 400;
			}
		} else {
			switch (linesCleared) {
				case 1: {
					score += 100;
					break;
				}
				case 2: {
					score += 300;
					break;
				}
				case 3: {
					score += 500;
					break;
				}
				case 4: {
					score += 800;
					break;
				}
			}
		}
	} else {
		comboCount = 0;
	}

	if (comboCount > 1) {
		score += 50 * comboCount;  // No levels (yet)
	}

	if (linesCleared == 0 && lastWasTSpin) {
		score += 400;
	}
}
