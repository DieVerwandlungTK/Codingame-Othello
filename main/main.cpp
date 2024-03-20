#include "TreeSearchAI.hpp"
#include "OthelloTypes.hpp"
#include "evaluate.hpp"

#include <iostream>

int main(){
    int color;
    std::cin >> color;
    Color AIColor = Color(color);
    TreeSearchAI AI(1, evalPieceCount);

    int64_t blackPieces, whitePieces;
    while(1){
        std::cin >> blackPieces >> whitePieces;
        AI.setBoard(blackPieces, whitePieces);
        std::cout << AI.getMove(AIColor) << std::endl;
    }
    return 0;
}