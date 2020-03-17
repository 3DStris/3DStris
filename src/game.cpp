#include <3dstris/game.hpp>
#include <3dstris/state.hpp>
#include <3dstris/util/colorstextures.hpp>

Game::Game() {
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();

	top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

	imageSheet = C2D_SpriteSheetLoad("romfs:/gfx/images.t3x");

	states.reserve(1);
}

Game::~Game() {
	C2D_SpriteSheetFree(imageSheet);

	C3D_RenderTargetDelete(top);
	C3D_RenderTargetDelete(bottom);

	C2D_Fini();
	C3D_Fini();
	gfxExit();
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
		C2D_TargetClear(this->top, Theme::BLACK);
	}
	if (bottom) {
		C2D_TargetClear(this->bottom, Theme::BLACK);
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

const Theme& Game::getTheme() const noexcept {
	return config.theme;
}
