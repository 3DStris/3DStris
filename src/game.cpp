#include <3dstris/game.hpp>

Game::Game() {
	top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
	currentState = nullptr;
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

C3D_RenderTarget* Game::getTop() {
	return top;
}

C3D_RenderTarget* Game::getBottom() {
	return bottom;
}

void Game::setState(State* state) {
	auto black = C2D_Color32(0, 0, 0, 255);
	C2D_TargetClear(top, black);
	C2D_TargetClear(bottom, black);
	currentState = state;
}

State* Game::getState() {
	return currentState;
}
