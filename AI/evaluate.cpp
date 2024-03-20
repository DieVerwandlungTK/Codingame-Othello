#include "evaluate.hpp"
#include "Othello.hpp"

int evalPieceCount(uint64_t blackPieces, uint64_t whitePieces, Color color){
    int blackCount = OthelloBoard::popCount(blackPieces);
    int whiteCount = OthelloBoard::popCount(whitePieces);
    if(color == Color::BLACK){
        return blackCount - whiteCount;
    } else {
        return whiteCount - blackCount;
    }
}