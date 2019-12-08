#pragma once

#include <3ds.h>
#include <citro2d.h>
#include <3dstris/config.hpp>
#include <3dstris/state.hpp>
#include <iostream>
#include <nlohmann/json.hpp>

class State;
class Game {
   public:
	static Game& getInstance() {
		static Game game;
		return game;
	}

	void update(double dt);

	void draw();

	const Config& getConfig();

	C3D_RenderTarget* getTop();
	C3D_RenderTarget* getBottom();

	const C2D_SpriteSheet& getSpriteSheet();

	void setState(State* state, bool resetTop = false,
				  bool resetBottom = false);
	State* getState();

	bool exit = false;

   private:
	Game();

	Config config;

	C3D_RenderTarget* top;
	C3D_RenderTarget* bottom;

	State* currentState;
	C2D_SpriteSheet spriteSheet;
};
