#include "AIBase.hpp"
#include "Othello.hpp"

AIBase::AIBase(): board(OthelloBoard()){
}

void AIBase::setBoard(uint64_t blackPieces, uint64_t whitePieces){
    board.setBoard(blackPieces, whitePieces);
}

uint64_t AIBase::getMove(Color color){
    return 0;
}