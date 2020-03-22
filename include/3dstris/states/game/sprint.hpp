#pragma once

#include <3dstris/states/game/ingame.hpp>
#include <3dstris/util/text.hpp>

class Sprint final : public Ingame {
   public:
	explicit Sprint(const u16 lines);

	void update(double dt) override;
	void draw(bool bottom) const override;

	void reset() override;

   private:
	const String infoFormat;

	const u16 lines;

	Text infoText;
	double time = 0.0;

	const double startTime = 1.0;
	double startTimer = 0.0;
};
