#ifndef OTHELLO_HPP
#define OTHELLO_HPP

#include <cstdint>
#include <vector>

#include "OthelloTypes.hpp"

class OthelloBoard {
private:
    uint64_t blackPieces; // Bitboard representing black pieces
    uint64_t whitePieces; // Bitboard representing white pieces

    enum Masks{
        horizontalMask = 0x7e7e7e7e7e7e7e7e,
        verticalMask   = 0x00ffffffffffff00,
        diagonalMask   = 0x007e7e7e7e7e7e00
    };

public:
    static const int BOARD_SIZE = 8;
    static const int BOARD_SIZE_DB = 64;
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

    uint64_t getShiftedBoard(uint64_t bitboard, int dir)const;

    void makeMove(uint64_t move, Color color);

    void printBoard()const;

    static int popCount(uint64_t bitboard);

    std::vector<uint64_t> getPopPositions(uint64_t bitboard)const;
};

#endif