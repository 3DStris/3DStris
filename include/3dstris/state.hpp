#pragma once

#include <citro2d.h>
#include <3ds.h>
#include <3dstris/game.hpp>

class Game;
class State {
public:
	State(Game& game);

	virtual void update(double dt) = 0;

	virtual void draw(bool bottom) = 0;
protected:
	Game& game;
};