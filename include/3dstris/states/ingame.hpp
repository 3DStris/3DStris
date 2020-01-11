#pragma once

#include <3dstris/state.hpp>
#include <3dstris/piece.hpp>
#include <3dstris/util.hpp>
#include <3dstris/board.hpp>
#include <deque>
#include <random>

class Ingame : public State {
   public:
    Ingame();

    virtual void reset();

    void update(double dt) override;
    void draw(bool bottom) override;

   protected:
    Board board;
    const u32 tileSize;
    Vector2 origin;

    std::mt19937 bagRNG;
    const u32 upcoming;
    std::deque<PieceType> bag;

    Piece piece;

    PieceType hold;
    bool hasHeld;
};
