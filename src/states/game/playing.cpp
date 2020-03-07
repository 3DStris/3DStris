#include <3dstris/states/game/playing.hpp>
#include <3dstris/states/game/results.hpp>

Playing::Playing() : Ingame() {}

void Playing::update(const double dt) {
	if (piece.dead()) {
		game.pushState(make_unique<Results>(this));
	} else {
		Ingame::update(dt);
	}
}

void Playing::draw(const bool bottom) {
	if (bottom) {
		C2D_TargetClear(game.getBottom(), game.getTheme().background);
	} else {
		Ingame::draw(bottom);
	}
}
