#include <functional>
#include <vector>

#include "TreeSearchAI.hpp"

TreeSearchAI::TreeSearchAI(int depth, std::function<int(uint64_t, uint64_t, Color)> eval): AIBase(eval), depth(depth){
}

int TreeSearchAI::search(uint64_t blackPieces, uint64_t whitePieces, int depth, Color color, bool passed){
    if(depth == 0){
        return eval(blackPieces, whitePieces, color);
    }

    uint64_t legalMoves = board.getLegalMoves(color);
    if(legalMoves == 0){
        if(passed){
            return eval(blackPieces, whitePieces, color);
        }
        return search(blackPieces, whitePieces, depth-1, color, true);
    }
    
    std::vector<uint64_t> moves = board.getPopPositions(legalMoves);
    int bestScore = INT32_MIN;
    OthelloBoard tmp;
    for(uint64_t move: moves){
        tmp.setBoard(blackPieces, whitePieces);
        tmp.makeMove(move, color);
        int score = search(tmp.getBlackPieces(), tmp.getWhitePieces(), depth-1, color, false);
        bestScore = std::max(bestScore, score);
    }
    return bestScore;
}

uint64_t TreeSearchAI::getMove(Color color){
    uint64_t legalMoves = board.getLegalMoves(color);
    int bestScore = INT32_MIN;
    OthelloBoard tmp;
    std::vector<uint64_t> moves = board.getPopPositions(legalMoves);
    uint64_t bestMove = moves[0];
    for(uint64_t move: moves){
        tmp.setBoard(board.getBlackPieces(), board.getWhitePieces());
        tmp.makeMove(move, color);
        int score = search(tmp.getBlackPieces(), tmp.getWhitePieces(), depth-1, color, false);
        if(score > bestScore){
            bestScore = score;
            bestMove = move;
        }
    }
    return bestMove;
}