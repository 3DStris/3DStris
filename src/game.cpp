#include <3dstris/images.h>

#include <3dstris/game.hpp>
#include <3dstris/state.hpp>
#include <3dstris/util/colorstextures.hpp>

Game::Game()
	: imageSheet(C2D_SpriteSheetLoad("romfs:/gfx/images.t3x")),

	  top(C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT)),
	  bottom(C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT)) {
	states.reserve(1);
}

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

bool Game::isPressed(const u32 kDown, const Keybinds::Action action) const
	noexcept {
	return kDown & config.getKeybinds().get(action);
}

sds Game::translate(const char* __restrict key) const {
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
	if (states.size() <= 1) {
		return;
	}

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
}

Config& Game::getConfig() noexcept {
	return config;
}
const Config& Game::getConfig() const noexcept {
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

Keybinds& Game::getKeybinds() noexcept {
	return config.getKeybinds();
}
const Keybinds& Game::getKeybinds() const noexcept {
	return config.getKeybinds();
}
