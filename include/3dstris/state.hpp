#pragma once

#include <3dstris/game.hpp>

class State {
   public:
	State();
	virtual ~State() = default;

	State(const State&) = delete;
	State(State&&) = delete;
	State& operator=(const State&) = delete;
	State& operator=(State&&) = delete;

	virtual void update(const double dt) = 0;
	virtual void draw(const bool bottom) = 0;

   protected:
	Game& game;
};
