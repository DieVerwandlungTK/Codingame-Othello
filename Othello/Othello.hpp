#ifndef OTHELLO_HPP
#define OTHELLO_HPP

#include "OthelloTypes.hpp"
#include <cstdint>

class OthelloBoard {
private:
    uint64_t blackPieces; // Bitboard representing black pieces
    uint64_t whitePieces; // Bitboard representing white pieces

public:
    // Initialize the starting position of the board
    OthelloBoard();

    // Function to get the bitboard representing black pieces
    uint64_t getBlackPieces()const;

    // Function to get the bitboard representing white pieces
    uint64_t getWhitePieces()const;

    // Function to check if a position is occupied by a piece
    bool isOccupied(uint64_t position)const;

    uint64_t getEmpty()const;

    uint64_t getLegalMoves(Color color)const;
};

#endif