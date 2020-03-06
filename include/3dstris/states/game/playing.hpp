#pragma once

#include <3dstris/states/game/ingame.hpp>

class Playing final : public Ingame {
   public:
	Playing();

	void update(double dt) override;
	void draw(bool bottom) override;
};
