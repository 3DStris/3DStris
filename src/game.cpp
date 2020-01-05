#include <3dstris/colors.hpp>
#include <3dstris/game.hpp>

Game::Game() : spriteSheet(C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x")) {
	top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
}

Game::~Game() {
	C2D_SpriteSheetFree(spriteSheet);
	C3D_RenderTargetDelete(top);
	C3D_RenderTargetDelete(bottom);
}

void Game::update(double dt) {
	getState().update(dt);
}

void Game::draw() {
	C2D_SceneBegin(top);
	getState().draw(false);

	C2D_SceneBegin(bottom);
	getState().draw(true);
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

void Game::pushState(std::unique_ptr<State> state, bool resetTop,
					 bool resetBottom) {
	states.push_back(std::move(state));

	reset(resetTop, resetBottom);
}

void Game::setState(std::unique_ptr<State> state, bool resetTop,
					bool resetBottom) {
	states.clear();

	pushState(std::move(state), resetTop, resetBottom);
}

void Game::popState(bool resetTop, bool resetBottom) {
	states.pop_back();

	reset(resetTop, resetBottom);
}

State& Game::getState() {
	return *states.back();
}

void Game::reset(bool top, bool bottom) {
	if (top) {
		C2D_TargetClear(this->top, BLACK);
	}
	if (bottom) {
		C2D_TargetClear(this->bottom, BLACK);
	}
}
