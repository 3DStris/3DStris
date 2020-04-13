#pragma once

#include <citro2d.h>

#include <3dstris/config.hpp>
#include <memory>

class State;
class Game {
   public:
	static Game& get() noexcept {
		static Game game;
		return game;
	}

	void update(double dt);

	void draw();

	bool isPressed(u32 kDown, Keybinds::Action action) const noexcept;

	String translate(const StringView key) const noexcept {
		return config.getL10n().get(key);
	}
	void loadLanguage(L10n::Language language) noexcept;

	C3D_RenderTarget* getTop() noexcept;
	C3D_RenderTarget* getBottom() noexcept;

	const C2D_SpriteSheet& getImageSheet() const noexcept;

	void pushState(std::unique_ptr<State> state, bool resetTop = false,
				   bool resetBottom = false);
	// You should most likely return from the state's update method after
	// calling either one of these, unless you like dereferencing null pointers
	void setState(std::unique_ptr<State> state, bool resetTop = false,
				  bool resetBottom = false);
	void popState(bool resetTop = false, bool resetBottom = false);

	State& getState();

	Config& getConfig() noexcept;
	const Config& getConfig() const noexcept;

	Games& getGames() noexcept;

	Keybinds& getKeybinds() noexcept;
	const Keybinds& getKeybinds() const noexcept;

	const Theme& getTheme() const noexcept;

	bool exit = false;

   private:
	Game() noexcept;
	~Game() noexcept;

	void reset(bool top, bool bottom) noexcept;

	C2D_SpriteSheet imageSheet;

	Config config;

	C3D_RenderTarget* top;
	C3D_RenderTarget* bottom;

	std::vector<std::unique_ptr<State>> states;
};
