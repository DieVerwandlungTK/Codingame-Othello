#include <iostream>

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

    const uint64_t horizontalMasked = opponentPieces & horizontalMask;
    const uint64_t verticalMasked = opponentPieces & verticalMask;
    const uint64_t diagonalMasked = opponentPieces & diagonalMask;

    tmp = horizontalMasked & (playerPieces << 1);
    for(int i = 0; i < 5; i++){
        tmp |= horizontalMasked & (tmp << 1);
    }
    legalMoves |= emptyPieces & (tmp << 1);

    tmp = horizontalMasked & (playerPieces >> 1);
    for(int i = 0; i < 5; i++){
        tmp |= horizontalMasked & (tmp >> 1);
    }
    legalMoves |= emptyPieces & (tmp >> 1);

    tmp = verticalMasked & (playerPieces << 8);
    for(int i = 0; i < 5; i++){
        tmp |= verticalMasked & (tmp << 8);
    }
    legalMoves |= emptyPieces & (tmp << 8);

    tmp = verticalMasked & (playerPieces >> 8);
    for(int i = 0; i < 5; i++){
        tmp |= verticalMasked & (tmp >> 8);
    }
    legalMoves |= emptyPieces & (tmp >> 8);

    tmp = diagonalMasked & (playerPieces << 7);
    for(int i = 0; i < 5; i++){
        tmp |= diagonalMasked & (tmp << 7);
    }
    legalMoves |= emptyPieces & (tmp << 7);

    tmp = diagonalMasked & (playerPieces >> 7);
    for(int i = 0; i < 5; i++){
        tmp |= diagonalMasked & (tmp >> 7);
    }
    legalMoves |= emptyPieces & (tmp >> 7);

    tmp = diagonalMasked & (playerPieces << 9);
    for(int i = 0; i < 5; i++){
        tmp |= diagonalMasked & (tmp << 9);
    }
    legalMoves |= emptyPieces & (tmp << 9);

    tmp = diagonalMasked & (playerPieces >> 9);
    for(int i = 0; i < 5; i++){
        tmp |= diagonalMasked & (tmp >> 9);
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
}

void OthelloBoard::printBoard()const{
    uint64_t mask = 0x8000000000000000;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(blackPieces & mask){
                std::cout << "B ";
            }else if(whitePieces & mask){
                std::cout << "W ";
            }else{
                std::cout << ". ";
            }
            mask >>= 1;
        }
        std::cout << std::endl;
    }
}