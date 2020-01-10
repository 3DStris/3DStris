#pragma once

#include <3dstris/board.hpp>
#include <3dstris/shapes.hpp>
#include <3dstris/ingame.hpp>
#include <3dstris/util.hpp>
#include <3dstris/util/text.hpp>
#include <deque>
#include <random>

class Sprint : public Ingame {
   public:
    Sprint();

	void update(double dt) override;
	void draw(bool bottom) override;

    void reset() override;

   private:
    Text lines;
    double time;
};
