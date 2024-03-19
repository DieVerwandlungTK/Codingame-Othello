#ifndef AIBASE_HPP
#define AIBASE_HPP

#include <cstdint>

#include "Othello.hpp"

class AIBase{
    private:
        OthelloBoard board;
    public:
        AIBase();
        void setBoard(uint64_t blackPieces, uint64_t whitePieces);
        virtual uint64_t getMove(Color color);
};

#endif