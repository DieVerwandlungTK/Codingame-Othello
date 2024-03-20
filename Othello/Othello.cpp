#include <iostream>
#include <vector>

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
    uint64_t tmp;

    const uint64_t horizontalMasked = opponentPieces & horizontalMask;
    const uint64_t verticalMasked = opponentPieces & verticalMask;
    const uint64_t diagonalMasked = opponentPieces & diagonalMask;

    tmp = horizontalMasked & (playerPieces << 1);
    for(int i = 0; i < 5; ++i){
        tmp |= horizontalMasked & (tmp << 1);
    }
    legalMoves |= emptyPieces & (tmp << 1);

    tmp = horizontalMasked & (playerPieces >> 1);
    for(int i = 0; i < 5; ++i){
        tmp |= horizontalMasked & (tmp >> 1);
    }
    legalMoves |= emptyPieces & (tmp >> 1);

    tmp = verticalMasked & (playerPieces << 8);
    for(int i = 0; i < 5; ++i){
        tmp |= verticalMasked & (tmp << 8);
    }
    legalMoves |= emptyPieces & (tmp << 8);

    tmp = verticalMasked & (playerPieces >> 8);
    for(int i = 0; i < 5; ++i){
        tmp |= verticalMasked & (tmp >> 8);
    }
    legalMoves |= emptyPieces & (tmp >> 8);

    tmp = diagonalMasked & (playerPieces << 7);
    for(int i = 0; i < 5; ++i){
        tmp |= diagonalMasked & (tmp << 7);
    }
    legalMoves |= emptyPieces & (tmp << 7);

    tmp = diagonalMasked & (playerPieces >> 7);
    for(int i = 0; i < 5; ++i){
        tmp |= diagonalMasked & (tmp >> 7);
    }
    legalMoves |= emptyPieces & (tmp >> 7);

    tmp = diagonalMasked & (playerPieces << 9);
    for(int i = 0; i < 5; ++i){
        tmp |= diagonalMasked & (tmp << 9);
    }
    legalMoves |= emptyPieces & (tmp << 9);

    tmp = diagonalMasked & (playerPieces >> 9);
    for(int i = 0; i < 5; ++i){
        tmp |= diagonalMasked & (tmp >> 9);
    }
    legalMoves |= emptyPieces & (tmp >> 9);

    return legalMoves;
}

void OthelloBoard::setBoard(uint64_t blackPieces, uint64_t whitePieces){
    this->blackPieces = blackPieces;
    this->whitePieces = whitePieces;
}

uint64_t OthelloBoard::getShiftedBoard(uint64_t bitboard, int dir)const{
    switch(dir){
        case 0:
            return (bitboard << 1) & 0xfefefefefefefefe;   // left
        case 1:
            return (bitboard >> 1) & 0x7f7f7f7f7f7f7f7f;   // right
        case 2:
            return (bitboard << 8) & 0xffffffffffffff00;   // up
        case 3:
            return (bitboard >> 8) & 0x00ffffffffffffff;   // down
        case 4:
            return (bitboard << 7) & 0x7f7f7f7f7f7f7f00;   // up right
        case 5:
            return (bitboard >> 7) & 0x00fefefefefefefe;   // down left
        case 6:
            return (bitboard << 9) & 0xfefefefefefefe00;   // up left
        case 7:
            return (bitboard >> 9) & 0x007f7f7f7f7f7f7f;   // down right
        default:
            return 0;
    }
}

void OthelloBoard::makeMove(uint64_t move, Color color){
    uint64_t playerPieces = (color == BLACK) ? blackPieces : whitePieces;
    uint64_t opponentPieces = (color == BLACK) ? whitePieces : blackPieces;
    uint64_t flippedPieces = 0;
    uint64_t tmp, mask;
    for(int i=0;i<8;++i){
        tmp = 0;
        mask = getShiftedBoard(move, i);
        while(mask && (mask & opponentPieces)){
            tmp |= mask;
            mask = getShiftedBoard(mask, i);
        }
        if(mask & playerPieces){
            flippedPieces |= tmp;
        }
    }
    if(color == BLACK){
        blackPieces ^= move | flippedPieces;
        whitePieces ^= flippedPieces;
    }
    else{
        whitePieces ^= move | flippedPieces;
        blackPieces ^= flippedPieces;
    }
}

void OthelloBoard::printBoard()const{
    uint64_t mask = 0x8000000000000000;
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
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

void OthelloBoard::printBoard2file()const{
    uint64_t mask = 0x8000000000000000;
    FILE *file = fopen("board.txt", "a+");
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            if(blackPieces & mask){
                fprintf(file, "B ");
            }else if(whitePieces & mask){
                fprintf(file, "W ");
            }else{
                fprintf(file, ". ");
            }
            mask >>= 1;
        }
        fprintf(file, "\n");
    }
    fprintf(file, "\n");
    fclose(file);
}

int OthelloBoard::popCount(uint64_t bitboard){
    bitboard = bitboard - ((bitboard >> 1) & 0x5555555555555555);

    bitboard = (bitboard & 0x3333333333333333) + ((bitboard >> 2) & 0x3333333333333333);

    bitboard = (bitboard + (bitboard >> 4)) & 0x0f0f0f0f0f0f0f0f;
    bitboard = bitboard + (bitboard >> 8);
    bitboard = bitboard + (bitboard >> 16);
    bitboard = bitboard + (bitboard >> 32);
    return bitboard & 0x7f;
}

std::vector<uint64_t> OthelloBoard::getPopPositions(uint64_t bitboard)const{
    uint64_t mask = 0x8000000000000000;
    std::vector<uint64_t> positions;
    while (mask) {
        if (bitboard & mask) {
            positions.push_back(mask);
        }
        mask >>= 1;
    }
    return positions;
}