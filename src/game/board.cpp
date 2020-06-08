#include <3dstris/game.hpp>
#include <3dstris/game/board.hpp>
#include <3dstris/gui.hpp>
#include <3dstris/util/colorstextures.hpp>

Board::Scoring::Scoring() noexcept
	: scoreDisplay(String::fromFmt("Score: %u", score), Pos{}, WH{0.5, 0.5}) {
	const WH scoreWH = scoreDisplay.getWH();
	scoreDisplay.setPos(Pos{4, SCREEN_HEIGHT - scoreWH.y - 1});
}
void Board::Scoring::reset() noexcept {
	score = 0;
	comboCount = 0;

	lastWasTSpin = false;
}
void Board::Scoring::updateDisplay() noexcept {
	scoreDisplay.setText(String::fromFmt("Score: %u", score));
}

Board::Board(const u32 width, const u32 height)
	: width(width), height(height), grid(width * height) {}

void Board::reset() {
	grid.assign(width * height, PieceType::NONE);

	scoring.reset();

	_linesCleared = 0;
	_droppedPieces = 0;
}

void Board::draw(const Pos origin, const u32 tileSize, const float outerThick,
				 const float gridThick) const {
	const Theme& theme = Game::get().getTheme();

	scoring.scoreDisplay.draw();

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

	if (scoring.lastWasTSpin) {
		scoring.score += 400;
	}

	if (linesCleared > 0) {
		++scoring.comboCount;
		if (scoring.lastWasTSpin) {
			for (u8 i = 0; i < linesCleared; ++i) {
				scoring.score += 400;
			}
		} else {
			switch (linesCleared) {
				case 1: {
					scoring.score += 100;
					break;
				}
				case 2: {
					scoring.score += 300;
					break;
				}
				case 3: {
					scoring.score += 500;
					break;
				}
				case 4: {
					scoring.score += 800;
					break;
				}
			}
		}
	} else {
		scoring.comboCount = 0;
	}

	if (scoring.comboCount > 1) {
		scoring.score += 50 * scoring.comboCount;  // No levels (yet)
	}

	scoring.updateDisplay();
}
