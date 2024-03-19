#include "AIBase.hpp"
#include "Othello.hpp"

AIBase::AIBase(std::function<int(uint64_t, uint64_t, Color)> eval): board(OthelloBoard()), eval(eval){
}

void AIBase::setBoard(uint64_t blackPieces, uint64_t whitePieces){
    board.setBoard(blackPieces, whitePieces);
}

uint64_t AIBase::getMove(Color color){
    return 0;
}