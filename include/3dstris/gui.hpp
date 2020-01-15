#pragma once

#include <3dstris/gui/button.hpp>
#include <3dstris/gui/widget.hpp>
#include <3dstris/util.hpp>
#include <vector>

class GUI {
   public:
	GUI(int width = BSCREEN_WIDTH, int height = BSCREEN_HEIGHT,
		Color primaryCol = Button::BUTTON, Color textCol = WHITE,
		Color pressedCol = Button::BUTTON_HELD,
		Color outlineCol = Button::BUTTON_OUTLINE);

	int getWidth() const noexcept;
	int getHeight() const noexcept;

	void update(double dt);
	void draw();

	template <typename T, typename... Targs>
	T& add(Targs&&... args) {
		widgets.push_back(make_unique<T>(*this, std::forward<Targs>(args)...));
		return static_cast<T&>(*widgets.back());
	}

	static void drawOutline(const Pos pos, const WH wh, const float scale = 2,
							const Color color = Button::BUTTON_OUTLINE,
							const float depth = 1);

	static void drawHLine(const Pos pos, const float w, const float scale = 2,
						  const Color color = Button::BUTTON_OUTLINE);

	static void drawVLine(const Pos pos, const float h, const float scale = 2,
						  const Color color = Button::BUTTON_OUTLINE);

	Color primaryCol, textCol, pressedCol, outlineCol;

   private:
	int width, height;
	std::vector<std::unique_ptr<Widget>> widgets;
	touchPosition previousTouch;
};
