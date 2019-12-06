#pragma once

#include <3ds.h>
#include <citro2d.h>
#include <functional>

const C2D_TextBuf textBuffer = C2D_TextBufNew(256);

class GUI;
class Button {
   public:
    Button(GUI& parent, float x, float y, float w, float h, const char* text,
           std::function<void()> onPress);
	void draw() const;
	void update(touchPosition touch);
    bool inside(float posX, float posY) const;
	void press();

   private:
	GUI& parent;
	float x, y, w, h;
	C2D_Text text;
	float textW, textH;
	float textSX, textSY;
	bool pressed;
	std::function<void()> onPress;
};
