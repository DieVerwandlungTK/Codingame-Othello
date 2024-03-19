#ifndef TREESEARCHAI_HPP
#define TREESEARCHAI_HPP

#include <cstdint>
#include <functional>

#include "AIBase.hpp"

class TreeSearchAI: public AIBase{
    private:
        int depth;
        int search(uint64_t blackPieces, uint64_t whitePieces, int depth, Color color, bool passed);
    public:
        TreeSearchAI(int depth, std::function<int(uint64_t, uint64_t, Color)> eval);

        uint64_t getMove(Color color) override;
};

#endif