#pragma once

#include <3dstris/game.hpp>
#include <3dstris/game/shapes.hpp>
#include <3dstris/util/math.hpp>

enum class PieceType { I, O, L, J, S, T, Z, NONE, INVALID };
enum class Direction { LEFT, RIGHT, UP, DOWN };

class Board;
class Piece {
   public:
	Piece(Board& board, const PieceShape& shape, PieceType type);
	Piece(Board& board, const PieceType type);

	void reset(const PieceShape& shape, PieceType type);
	void reset(PieceType type);

	void set() noexcept;
	bool hasSet() const noexcept { return setTimer >= setAfter; }

	void draw(Pos origin, u32 tileSize) const;
	static void draw(Pos origin, u32 tileSize, const PieceShape& shape,
					 PieceType type);

	bool move(Direction dir) noexcept;

	void rotate(bool ccw);

	bool collides(s32 offX, s32 offY) const noexcept;

	void update(double dt, u32 kDown);

	PieceType getType() const noexcept { return type; }

	bool dead() const noexcept { return _dead; }

   private:
	const Game& game;

	void updateMove(double dt, u32 kDown);

	Board& board;

	PieceType type;
	Pos pos;

	s32 rotation;

	C2D_Image sprite;
	PieceShape shape;

	double fallTimer;  /* timer that's between 0 and either fallAfter or
						  dropTimer */
	double fallAfter;  // how much time it takes for the piece to fall
	double dropTimer;  // replaces fallTimer when the soft drop button is held

	double setTimer; /* always 0 unless piece is colliding down, then it's
						incremented until it gets to setAfter */
	double setAfter; /* time it takes for piece to set after it has been
						colliding down */

	double das;
	Vector2d dasTimer;	// Vector2 as it needs one for left and right

	double arr;
	double arrTimer;

	bool _dead;
};
