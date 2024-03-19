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

uint64_t OthelloBoard::getLegalMoves()const{
    uint64_t  legalMoves = 0;
    const uint64_t empty = getEmpty();

    constexpr uint64_t horizontal_mask = 0x7E7E7E7E7E7E7E7E;
    constexpr uint64_t vertical_mask = 0x00FFFFFFFFFFFF00;
    constexpr uint64_t diagonal_mask = 0x007E7E7E7E7E7E00;

    uint64_t tmp = 0;
}