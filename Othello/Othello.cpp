#include "OthelloTypes.hpp"
#include "Othello.hpp"

// Definition of the default constructor
OthelloBoard::OthelloBoard() : blackPieces(0x0000000810000000), whitePieces(0x0000001008000000){
}

uint64_t OthelloBoard::getBlackPieces()const{
    return blackPieces;
}

uint64_t OthelloBoard::getWhitePieces()const{
    return whitePieces;
}

bool OthelloBoard::isOccupied(uint64_t position)const{
    return (blackPieces & position) || (whitePieces & position);
}

uint64_t OthelloBoard::getEmpty()const{
    return ~(blackPieces | whitePieces);
}

uint64_t OthelloBoard::getLegalMoves(Color color)const{
    const uint64_t emptyPieces = getEmpty();
    const uint64_t playerPieces = (color == BLACK) ? blackPieces : whitePieces;
    const uint64_t opponentPieces = (color == BLACK) ? whitePieces : blackPieces;
    uint64_t  legalMoves = 0;
    uint64_t tmp = 0;

    tmp = horizontalMask & (opponentPieces << 1);
    for(int i = 0; i < 5; i++){
        tmp |= horizontalMask & (tmp << 1);
    }
    legalMoves |= emptyPieces & (tmp << 1);

    tmp = horizontalMask & (opponentPieces >> 1);
    for(int i = 0; i < 5; i++){
        tmp |= horizontalMask & (tmp >> 1);
    }
    legalMoves |= emptyPieces & (tmp >> 1);

    tmp = verticalMask & (opponentPieces << 8);
    for(int i = 0; i < 5; i++){
        tmp |= verticalMask & (tmp << 8);
    }
    legalMoves |= emptyPieces & (tmp << 8);

    tmp = verticalMask & (opponentPieces >> 8);
    for(int i = 0; i < 5; i++){
        tmp |= verticalMask & (tmp >> 8);
    }
    legalMoves |= emptyPieces & (tmp >> 8);

    tmp = diagonalMask & (opponentPieces << 7);
    for(int i = 0; i < 5; i++){
        tmp |= diagonalMask & (tmp << 7);
    }
    legalMoves |= emptyPieces & (tmp << 7);

    tmp = diagonalMask & (opponentPieces >> 7);
    for(int i = 0; i < 5; i++){
        tmp |= diagonalMask & (tmp >> 7);
    }
    legalMoves |= emptyPieces & (tmp >> 7);

    tmp = diagonalMask & (opponentPieces << 9);
    for(int i = 0; i < 5; i++){
        tmp |= diagonalMask & (tmp << 9);
    }
    legalMoves |= emptyPieces & (tmp << 9);

    tmp = diagonalMask & (opponentPieces >> 9);
    for(int i = 0; i < 5; i++){
        tmp |= diagonalMask & (tmp >> 9);
    }
    legalMoves |= emptyPieces & (tmp >> 9);

    return legalMoves;
}

void OthelloBoard::setBoard(uint64_t blackPieces, uint64_t whitePieces){
    this->blackPieces = blackPieces;
    this->whitePieces = whitePieces;
}

void OthelloBoard::makeMove(uint64_t move, Color color){
    uint64_t playerPieces = (color == BLACK) ? blackPieces : whitePieces;
    uint64_t opponentPieces = (color == BLACK) ? whitePieces : blackPieces;
    uint64_t flippedPieces = 0;
    uint64_t tmp = 0;

    tmp = horizontalMask & (opponentPieces << 1);
    for(int i = 0; i < 5; i++){
        tmp |= horizontalMask & (tmp << 1);
    }
    flippedPieces |= tmp & (move << 1);

    tmp = horizontalMask & (opponentPieces >> 1);
    for(int i = 0; i < 5; i++){
        tmp |= horizontalMask & (tmp >> 1);
    }
    flippedPieces |= tmp & (move >> 1);

    tmp = verticalMask & (opponentPieces << 8);
    for(int i = 0; i < 5; i++){
        tmp |= verticalMask & (tmp << 8);
    }
    flippedPieces |= tmp & (move << 8);

    tmp = verticalMask & (opponentPieces >> 8);
    for(int i = 0; i < 5; i++){
        tmp |= verticalMask & (tmp >> 8);
    }
    flippedPieces |= tmp & (move >> 8);

    tmp = diagonalMask & (opponentPieces << 7);
    for(int i = 0; i < 5; i++){
        tmp |= diagonalMask & (tmp << 7);
    }
    flippedPieces |= tmp & (move << 7);

    tmp = diagonalMask & (opponentPieces >> 7);
    for(int i = 0; i < 5; i++){
        tmp |= diagonalMask & (tmp >> 7);
    }
    flippedPieces |= tmp & (move >> 7);

    tmp = diagonalMask & (opponentPieces << 9);
    for(int i = 0; i < 5; i++){
        tmp |= diagonalMask & (tmp << 9);
    }
    flippedPieces |= tmp & (move << 9);

    tmp = diagonalMask & (opponentPieces >> 9);
    for(int i = 0; i < 5; i++){
        tmp |= diagonalMask & (tmp >> 9);
    }
    flippedPieces |= tmp & (move >> 9);
}