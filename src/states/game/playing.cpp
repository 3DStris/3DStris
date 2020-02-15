#include <3dstris/states/game/paused.hpp>
#include <3dstris/states/game/playing.hpp>
#include <3dstris/states/game/results.hpp>

Playing::Playing() : Ingame() {}

void Playing::update(const double dt) {
	if (piece.dead()) {
		game.pushState(make_unique<Results>(this));
		return;
	}

	Ingame::update(dt);
}
