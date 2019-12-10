#pragma once

#include <citro2d.h>
#include <3dstris/gui.hpp>
#include <3dstris/state.hpp>
#include <3dstris/states/playing.hpp>
#include <3dstris/util.hpp>

class ConfigFailed : public State {
   public:
	ConfigFailed();
	virtual ~ConfigFailed();

	void update(double dt) override;
	void draw(bool bottom) override;

   private:
	C2D_TextBuf failedTextBuf;
	C2D_Text failedText;

	Color colBackground;

	GUI gui;
};
