#include <3dstris/states/mainmenu.hpp>
#include <3dstris/states/paused.hpp>
#include <3dstris/states/playing.hpp>
#include <3dstris/states/results.hpp>

Playing::Playing() : Ingame() {}

void Playing::update(double dt) {
	u32 kDown = hidKeysDown();

	if (kDown & KEY_START) {
		game.pushState(make_unique<Paused>(this));
		return;
	}

	if (piece.dead()) {
		game.pushState(make_unique<Results>(this));
		return;
	}

	Ingame::update(dt);
}
