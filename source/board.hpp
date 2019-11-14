#pragma once

#include "piece.hpp"
#include <vector>

class Board {
	private:
		std::vector<PieceType> grid;
	public:
		int width;
		int height;

		Board(int width, int height);

		bool inside(int x, int y);
		bool inside(Vector2 pos);

		void set(int x, int y, PieceType t);
		void set(Vector2 pos, PieceType t);

		PieceType get(int x, int y);
		PieceType get(Vector2 pos);
		
		void draw(Vector2 origin, int tileSize);

		void clearLines();
};