#pragma once

#include <3dstris/states/game/ingame.hpp>

class Playing : public Ingame {
   public:
	Playing();

	void update(const double dt) override;
	void draw(const bool bottom) override;
};
