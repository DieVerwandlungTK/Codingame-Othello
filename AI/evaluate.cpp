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

int evalWeight(uint64_t blackPieces, uint64_t whitePieces, Color color){
    static const int weight[OthelloBoard::BOARD_SIZE_DB] = {
        100, -20, 10, 5, 5, 10, -20, 100,
        -20, -50, -2, -2, -2, -2, -50, -20,
        10, -2, -1, -1, -1, -1, -2, 10,
        5, -2, -1, -1, -1, -1, -2, 5,
        5, -2, -1, -1, -1, -1, -2, 5,
        10, -2, -1, -1, -1, -1, -2, 10,
        -20, -50, -2, -2, -2, -2, -50, -20,
        100, -20, 10, 5, 5, 10, -20, 100
    };

    int blackWeight = 0;
    int whiteWeight = 0;
    uint64_t mask = 0x8000000000000000;
    for(int i = 0; i < OthelloBoard::BOARD_SIZE_DB; ++i){
        if(blackPieces & mask){
            blackWeight += weight[i];
        }
        if(whitePieces & mask){
            whiteWeight += weight[i];
        }
        mask >>= 1;
    }
    if(color == Color::BLACK){
        return blackWeight - whiteWeight;
    } else {
        return whiteWeight - blackWeight;
    }
}