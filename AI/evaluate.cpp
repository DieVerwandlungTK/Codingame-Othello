#include "evaluate.hpp"
#include "Othello.hpp"

int evalPieceCount(int64_t blackPieces, int64_t whitePieces, Color color){
    int blackCount = OthelloBoard::popCount(blackPieces);
    int whiteCount = OthelloBoard::popCount(whitePieces);
    if(color == Color::BLACK){
        return blackCount - whiteCount;
    } else {
        return whiteCount - blackCount;
    }
}