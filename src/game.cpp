#include <3dstris/colors.hpp>
#include <3dstris/game.hpp>

Game::Game()
	: currentState(nullptr),
	  spriteSheet(C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x")) {
	top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
}

Game::~Game() {
	C2D_SpriteSheetFree(spriteSheet);
	C3D_RenderTargetDelete(top);
	C3D_RenderTargetDelete(bottom);
}

void Game::update(double dt) {
	currentState->update(dt);
}

void Game::draw() {
	C2D_SceneBegin(top);
	currentState->draw(false);

	C2D_SceneBegin(bottom);
	currentState->draw(true);
}

Config& Game::getConfig() {
	return config;
}

C3D_RenderTarget* Game::getTop() {
	return top;
}

C3D_RenderTarget* Game::getBottom() {
	return bottom;
}

const C2D_SpriteSheet& Game::getSpriteSheet() {
	return spriteSheet;
}

void Game::setState(std::unique_ptr<State> state, bool resetTop,
					bool resetBottom) {
	currentState = std::move(state);

	if (resetTop)
		C2D_TargetClear(top, BLACK);
	if (resetBottom)
		C2D_TargetClear(bottom, BLACK);
}

State& Game::getState() {
	return *currentState;
}
