#pragma once

#include <citro2d.h>
#include <3ds.h>

class State {
public:
	State(bool usesBottomScreen);

	virtual void update(double dt) = 0;

	virtual void draw(bool bottom) = 0;

	C3D_RenderTarget* getTop();
	C3D_RenderTarget* getBottom();

	bool hasBottom();
	bool exit();
protected:
	bool _exit = false;
private:
	C3D_RenderTarget* top;
	C3D_RenderTarget* bottom;
	
	bool _hasBottom = false;
};