#ifndef OTHELLO_HPP
#define OTHELLO_HPP

#include "OthelloTypes.hpp"
#include <cstdint>

class OthelloBoard {
private:
    uint64_t blackPieces; // Bitboard representing black pieces
    uint64_t whitePieces; // Bitboard representing white pieces

    enum Masks{
        horizontalMask = 0x7E7E7E7E7E7E7E7E,
        verticalMask   = 0x00FFFFFFFFFFFF00,
        diagonalMask   = 0x007E7E7E7E7E7E00
    };

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

    void setBoard(uint64_t blackPieces, uint64_t whitePieces);

    void makeMove(uint64_t move, Color color);

    void printBoard()const;
};

#endif