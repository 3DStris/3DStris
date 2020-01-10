#pragma once

#include <3dstris/ingame.hpp>

class Playing : public Ingame {
   public:
	Playing();

	void update(double dt) override;
};
