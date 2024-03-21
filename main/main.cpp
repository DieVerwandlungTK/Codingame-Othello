#include "TreeSearchAI.hpp"
#include "NegaAlphaAI.hpp"
#include "evaluate.hpp"

#include <iostream>

int main(){
    int color;
    std::cin >> color;
    Color AIColor = Color(color);
    NegaAlphaAI AI(AIColor, 8, evalWeight);

    uint64_t blackPieces, whitePieces;
    while(1){
        std::cin >> blackPieces >> whitePieces;
        AI.setBoard(blackPieces, whitePieces);
        std::cout << AI.getMove() << std::endl;
    }
    return 0;
}