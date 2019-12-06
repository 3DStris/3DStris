#pragma once

#include <3ds.h>
#include <citro2d.h>
#include <3dstris/state.hpp>

class State;
class Game {
   public:
    static Game& getInstance() {
        static Game game;
        return game;
    }

	void update(double dt);

	void draw();

	C3D_RenderTarget* getTop();
	C3D_RenderTarget* getBottom();

    void setState(State* state, bool resetTop = false,
                  bool resetBottom = false);
	State* getState();

    bool exit = false;

   private:
    Game();

	C3D_RenderTarget* top;
	C3D_RenderTarget* bottom;

	State* currentState;
};
