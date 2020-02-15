#include <3dstris/images.h>
#include <3dstris/colors.hpp>
#include <3dstris/game.hpp>
#include <3dstris/state.hpp>

Game::Game()
	: imageSheet(C2D_SpriteSheetLoad("romfs:/gfx/images.t3x")),

	  top(C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT)),
	  bottom(C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT)) {}

Game::~Game() {
	C2D_SpriteSheetFree(imageSheet);

	C3D_RenderTargetDelete(top);
	C3D_RenderTargetDelete(bottom);
}

void Game::update(const double dt) {
	getState().update(dt);
}

void Game::draw() {
	C2D_SceneBegin(top);
	getState().draw(false);

	C2D_SceneBegin(bottom);
	getState().draw(true);
}

sds Game::translate(const char* key) const {
	return config.getL10n().get(key);
}
void Game::loadLanguage(const L10n::Language language) {
	config.getL10n().loadLanguage(language);
}

C3D_RenderTarget* Game::getTop() {
	return top;
}
C3D_RenderTarget* Game::getBottom() {
	return bottom;
}

const C2D_SpriteSheet& Game::getImageSheet() const noexcept {
	return imageSheet;
}

void Game::pushState(std::unique_ptr<State> state, const bool resetTop,
					 const bool resetBottom) {
	states.push_back(std::move(state));

	reset(resetTop, resetBottom);
}

void Game::setState(std::unique_ptr<State> state, const bool resetTop,
					const bool resetBottom) {
	states.clear();

	pushState(std::move(state), resetTop, resetBottom);
}

void Game::popState(const bool resetTop, const bool resetBottom) {
	states.pop_back();

	reset(resetTop, resetBottom);
}

State& Game::getState() {
	return *states.back();
}

void Game::reset(const bool top, const bool bottom) {
	if (top) {
		C2D_TargetClear(this->top, BLACK);
	}
	if (bottom) {
		C2D_TargetClear(this->bottom, BLACK);
	}
	states.shrink_to_fit();
}

Config& Game::getConfig() noexcept {
	return config;
}

Games& Game::getGames() noexcept {
	return config.getGames();
}

L10n& Game::getL10n() noexcept {
	return config.getL10n();
}
const L10n& Game::getL10n() const noexcept {
	return config.getL10n();
}
