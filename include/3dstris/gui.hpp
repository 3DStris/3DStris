#pragma once

#include <3dstris/gui/button.hpp>
#include <3dstris/util.hpp>
#include <vector>

class GUI {
   public:
	GUI(u32 width = BSCREEN_WIDTH, u32 height = BSCREEN_HEIGHT,
		Color primaryCol = Button::BUTTON, Color textCol = WHITE,
		Color pressedCol = Button::BUTTON_HELD,
		Color outlineCol = Button::BUTTON_OUTLINE);

	u32 getWidth() const noexcept;
	u32 getHeight() const noexcept;

	void update(double dt);
	void draw() const;

	template <typename T, typename... Args>
	T& add(Args&&... args) {
		static_assert(std::is_convertible<T*, Widget*>::value,
					  "T* must be convertible to Widget*");

		widgets.push_back(make_unique<T>(*this, std::forward<Args>(args)...));
		return static_cast<T&>(*widgets.back());
	}

	static void drawOutline(Pos pos, WH wh, float scale = 2,
							Color color = Button::BUTTON_OUTLINE,
							float depth = 1);

	static void drawHLine(Pos pos, float w, float scale = 2,
						  Color color = Button::BUTTON_OUTLINE,
						  float depth = 0.5f);

	static void drawVLine(Pos pos, float h, float scale = 2,
						  Color color = Button::BUTTON_OUTLINE,
						  float depth = 0.5f);

	Color primaryCol, textCol, pressedCol, outlineCol;

   private:
	u32 width, height;
	std::vector<std::unique_ptr<Widget>> widgets;
	touchPosition previousTouch;
};
