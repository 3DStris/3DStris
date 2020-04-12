#pragma once

#include <3dstris/gui/widgets/button.hpp>
#include <3dstris/gui/widgets/panel.hpp>
#include <3dstris/state.hpp>

class BaseSettings : public State {
   public:
	BaseSettings(const StringView titleKey) noexcept;

	void update(double dt) override;
	void draw(bool bottom) const override;

   protected:
	// The constructor can only be called once, so I guess it's okay. However,
	// that in and of itself was changed only to accomodate for this. It would
	// be preferable for this design to be scrapped entirely.
	friend Config;

	static BaseConfig config;

	GUI gui;

   private:
	Text title;
	Panel tip;
	Text tipText;

	Panel& panel;

	Button& save;
	Button& cancel;
};
