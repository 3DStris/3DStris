#pragma once

#include <3ds.h>
#include <citro2d.h>
#include <functional>

class GUI;
class Button {
   public:
	Button(GUI& parent, float x, float y, float w, float h, const char* text,
		   std::function<void()> onPress);
	~Button();

	void setText(const char* text, bool resizeBuf = true);

	void draw() const;
	void update(touchPosition touch);

	bool inside(float posX, float posY) const;
	void press();

   private:
	GUI& parent;

	C2D_TextBuf textBuf;

	float x, y, w, h;
	C2D_Text text;
	float textW, textH;
	float textSX, textSY;
	bool pressed;
	std::function<void()> onPress;
};
