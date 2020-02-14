#include <3dstris/states/paused.hpp>
#include <3dstris/states/playing.hpp>
#include <3dstris/states/results.hpp>

Playing::Playing() : Ingame() {}

void Playing::update(const double dt) {
	if (piece.dead()) {
		game.pushState(make_unique<Results>(this));
		return;
	}

	Ingame::update(dt);
}
