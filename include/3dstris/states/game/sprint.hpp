#pragma once

#include <3dstris/states/game/ingame.hpp>
#include <3dstris/util/text.hpp>

class Sprint final : public Ingame {
   public:
	explicit Sprint(const u16 lines);
	~Sprint() override;

	void update(const double dt) override;
	void draw(const bool bottom) override;

	void reset() override;

   private:
	const sds infoFormat;

	const u16 lines;

	Text infoText;
	double time;

	const double startTime = 1.0;
	double startTimer;
};
