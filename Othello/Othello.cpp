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