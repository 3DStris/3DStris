#pragma once

#include <citro2d.h>

#include <3dstris/config.hpp>

class State;
class Game {
   public:
	static Game& get() {
		static Game game;
		return game;
	}

	void update(double dt);

	void draw();

	bool isPressed(u32 kDown, Keybinds::Action action) const noexcept;

	sds translate(const char* __restrict key) const;
	void loadLanguage(L10n::Language language);

	C3D_RenderTarget* getTop();
	C3D_RenderTarget* getBottom();

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

	L10n& getL10n() noexcept;
	const L10n& getL10n() const noexcept;

	Keybinds& getKeybinds() noexcept;
	const Keybinds& getKeybinds() const noexcept;

	const Theme& getTheme() const noexcept;

	bool exit = false;

   private:
	Game();
	~Game();

	void reset(bool top, bool bottom);

	C2D_SpriteSheet imageSheet;

	Config& config;

	C3D_RenderTarget* top;
	C3D_RenderTarget* bottom;

	std::vector<std::unique_ptr<State>> states;
};
