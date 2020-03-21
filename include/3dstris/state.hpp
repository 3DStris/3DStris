#pragma once

class Game;
class State {
   public:
	State();
	virtual ~State() = default;

	virtual void update(double dt) = 0;
	virtual void draw(bool bottom) const = 0;

   protected:
	Game& game;
};
