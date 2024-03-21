#include "AIBase.hpp"
#include "Othello.hpp"

AIBase::AIBase(Color AIColor, std::function<int(uint64_t, uint64_t, Color)> eval): board(OthelloBoard()), AIColor(AIColor), eval(eval){
}

void AIBase::setBoard(uint64_t blackPieces, uint64_t whitePieces){
    board.setBoard(blackPieces, whitePieces);
}

uint64_t AIBase::getMove(){
    return 0;
}