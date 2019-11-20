#include <3dstris/state.hpp>

State::State(bool usesBottomScreen) {
	_hasBottom = usesBottomScreen;
	top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	if (usesBottomScreen) {
		bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
	} else {
		bottom = nullptr;
		consoleInit(GFX_BOTTOM, nullptr);
	}
}

C3D_RenderTarget* State::getTop() {
	return top;
}

C3D_RenderTarget* State::getBottom() {
	return bottom;
}

bool State::hasBottom() {
	return _hasBottom;
}

bool State::exit() {
	return _exit;
}