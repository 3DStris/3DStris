#pragma once

#include <3dstris/game.hpp>
#include <3dstris/gui/widgets/button.hpp>
#include <3dstris/util/draw.hpp>
#include <3dstris/util/pointer.hpp>

class GUI {
   public:
	GUI(u32 width = BSCREEN_WIDTH, u32 height = BSCREEN_HEIGHT) noexcept;

	u32 getWidth() const noexcept;
	u32 getHeight() const noexcept;

	void update(double dt);
	void draw() const;

	static const Theme& getTheme() noexcept;

	template <typename T, typename... Args>
	T& add(Args&&... args) {
		static_assert(std::is_convertible<T*, Widget*>::value,
					  "T* must be convertible to Widget*");

		widgets.push_back(make_unique<T>(*this, std::forward<Args>(args)...));
		return static_cast<T&>(*widgets.back());
	}

	static void drawOutline(Pos pos, WH wh, float scale = 2,
							Color color = getTheme().buttonOutline,
							float depth = 1) noexcept;

	static void drawHLine(Pos pos, float w, float scale = 2,
						  Color color = getTheme().buttonOutline,
						  float depth = 0.5f) noexcept;

	static void drawVLine(Pos pos, float h, float scale = 2,
						  Color color = getTheme().buttonOutline,
						  float depth = 0.5f) noexcept;

   private:
	u32 width, height;
	std::vector<std::unique_ptr<Widget>> widgets;
	touchPosition previousTouch;
};
