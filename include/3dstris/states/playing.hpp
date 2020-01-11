#pragma once

#include <3dstris/states/ingame.hpp>

class Playing : public Ingame {
   public:
	Playing();

	void update(const double dt) override;
};
