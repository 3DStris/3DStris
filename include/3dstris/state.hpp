#pragma once

#include <3ds.h>
#include <citro2d.h>
#include <3dstris/game.hpp>

class Game;
class State {
   public:
	State();
	virtual ~State() = default;

	virtual void update(double dt) = 0;
	virtual void draw(bool bottom) = 0;

   protected:
	Game& game;
};
