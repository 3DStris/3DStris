#pragma once

#include <citro2d.h>
#include <3dstris/config.hpp>
#include <3dstris/state.hpp>
#include <memory>

class State;
class Game {
   public:
	static Game& getInstance() {
		static Game game;
		return game;
	}

	void update(const double dt);

	void draw();

	Config& getConfig() noexcept;
	Games& getGames() noexcept;

	sds translate(const char* key) const;
	void loadLanguage(const L10n::Language language);

	C3D_RenderTarget* getTop();
	C3D_RenderTarget* getBottom();

	const C2D_SpriteSheet& getSpriteSheet() const noexcept;

	void pushState(std::unique_ptr<State> state, const bool resetTop = false,
				   const bool resetBottom = false);
	void setState(std::unique_ptr<State> state, const bool resetTop = false,
				  const bool resetBottom = false);
	void popState(const bool resetTop = false, const bool resetBottom = false);
	State& getState();

	bool exit = false;

   private:
	Game();
	~Game();

	void reset(const bool top, const bool bottom);

	C2D_SpriteSheet spriteSheet;

	Config config;

	C3D_RenderTarget* top;
	C3D_RenderTarget* bottom;

	std::vector<std::unique_ptr<State>> states;
};
