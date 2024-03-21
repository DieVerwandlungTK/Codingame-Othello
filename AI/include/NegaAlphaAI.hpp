#ifndef NEGAALPHA_HPP
#define NEGAALPHA_HPP

#include "AIBase.hpp"

class NegaAlphaAI: public AIBase{
    private:
        int depth;
        int search(uint64_t blackPieces, uint64_t whitePieces, int depth, Color color, bool passed, int alpha, int beta);
        
    public:
        NegaAlphaAI(Color AIColor, int depth, std::function<int(uint64_t, uint64_t, Color)> eval);

        uint64_t getMove() override;
};

#endif