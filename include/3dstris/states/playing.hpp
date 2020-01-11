#pragma once

#include <3dstris/states/ingame.hpp>

class Playing : public Ingame {
   public:
	Playing();

	void update(double dt) override;
};
