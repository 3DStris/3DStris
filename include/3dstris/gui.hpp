#pragma once

#include <3dstris/gui/button.hpp>
#include <3dstris/gui/widget.hpp>
#include <3dstris/util.hpp>
#include <vector>

class GUI {
   public:
	GUI(const u16 width = BSCREEN_WIDTH, const u16 height = BSCREEN_HEIGHT,
		const Color primaryCol = Button::BUTTON, const Color textCol = WHITE,
		const Color pressedCol = Button::BUTTON_HELD,
		const Color outlineCol = Button::BUTTON_OUTLINE);

	u16 getWidth() const noexcept;
	u16 getHeight() const noexcept;

	void update(double dt);
	void draw() const;

	template <typename T, typename... Targs>
	T& add(Targs&&... args) {
		widgets.push_back(make_unique<T>(*this, std::forward<Targs>(args)...));
		return static_cast<T&>(*widgets.back());
	}

	static void drawOutline(const Pos pos, const WH wh, const float scale = 2,
							const Color color = Button::BUTTON_OUTLINE,
							const float depth = 1);

	static void drawHLine(const Pos pos, const float w, const float scale = 2,
						  const Color color = Button::BUTTON_OUTLINE,
						  const float depth = 0.5f);

	static void drawVLine(const Pos pos, const float h, const float scale = 2,
						  const Color color = Button::BUTTON_OUTLINE,
						  const float depth = 0.5f);

	Color primaryCol, textCol, pressedCol, outlineCol;

   private:
	u16 width, height;
	std::vector<std::unique_ptr<Widget>> widgets;
	touchPosition previousTouch;
};
