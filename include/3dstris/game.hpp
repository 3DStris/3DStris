#pragma once

#include <3dstris/config.hpp>
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

	Config& getConfig();

	C3D_RenderTarget* getTop();
	C3D_RenderTarget* getBottom();

	const C2D_SpriteSheet& getSpriteSheet();

	void setState(std::unique_ptr<State> state, bool resetTop = false,
				  bool resetBottom = false);
	State& getState();

	bool exit = false;

   private:
	Game();
	~Game();

	Config config;

	C3D_RenderTarget* top;
	C3D_RenderTarget* bottom;

	std::unique_ptr<State> currentState;
	C2D_SpriteSheet spriteSheet;
};
