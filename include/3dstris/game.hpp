#pragma once

#include <citro2d.h>
#include <3ds.h>
#include <3dstris/state.hpp>

class State;
class Game {
public:
	bool exit = false;

	Game();

	void update(double dt);

	void draw();

	C3D_RenderTarget* getTop();
	C3D_RenderTarget* getBottom();

	void setState(State* state);
	State* getState();
private:
	C3D_RenderTarget* top;
	C3D_RenderTarget* bottom;
	
	State* currentState;
};