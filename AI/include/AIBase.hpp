#ifndef AIBASE_HPP
#define AIBASE_HPP

#include <cstdint>
#include <functional>

#include "Othello.hpp"

class AIBase{
    private:
        OthelloBoard board;
        std::function<int(uint64_t, uint64_t)> eval;

    protected:
        AIBase(std::function<int(uint64_t, uint64_t)> eval);
    public:
        void setBoard(uint64_t blackPieces, uint64_t whitePieces);
        virtual uint64_t getMove(Color color);
};

#endif