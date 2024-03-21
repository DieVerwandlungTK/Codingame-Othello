#ifndef AIBASE_HPP
#define AIBASE_HPP

#include <functional>

#include "Othello.hpp"

class AIBase{
    protected:
        OthelloBoard board;
        Color AIColor;
        std::function<int(uint64_t, uint64_t, Color)> eval;

        AIBase(Color AIColor, std::function<int(uint64_t, uint64_t, Color)> eval);
    public:
        void setBoard(uint64_t blackPieces, uint64_t whitePieces);
        virtual uint64_t getMove();
};

#endif