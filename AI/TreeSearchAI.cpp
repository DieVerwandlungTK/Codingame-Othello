#include "TreeSearchAI.hpp"

TreeSearchAI::TreeSearchAI(Color AIColor, int depth, std::function<int(uint64_t, uint64_t, Color)> eval): AIBase(AIColor, eval), depth(depth){
}

int TreeSearchAI::search(uint64_t blackPieces, uint64_t whitePieces, int depth, bool passed){
    if(depth == 0){
        return eval(blackPieces, whitePieces, AIColor);
    }

    std::vector<uint64_t> legalMoves = board.getPopPositions(board.getLegalMoves(AIColor));
    if(legalMoves.empty()){
        if(passed){
            return eval(blackPieces, whitePieces, AIColor);
        }
        return search(blackPieces, whitePieces, depth-1, true);
    }
    
    int bestScore = INT32_MIN;
    OthelloBoard tmp;
    for(uint64_t move: legalMoves){
        tmp.setBoard(blackPieces, whitePieces);
        tmp.makeMove(move, AIColor);
        int score = search(tmp.getBlackPieces(), tmp.getWhitePieces(), depth-1, false);
        bestScore = std::max(bestScore, score);
    }
    return bestScore;
}

uint64_t TreeSearchAI::getMove(){
    uint64_t legalMoves = board.getLegalMoves(AIColor);
    int bestScore = INT32_MIN;
    OthelloBoard tmp;
    std::vector<uint64_t> moves = board.getPopPositions(legalMoves);
    uint64_t bestMove = moves[0];
    for(uint64_t move: moves){
        tmp.setBoard(board.getBlackPieces(), board.getWhitePieces());
        tmp.makeMove(move, AIColor);
        int score = search(tmp.getBlackPieces(), tmp.getWhitePieces(), depth-1, false);
        if(score > bestScore){
            bestScore = score;
            bestMove = move;
        }
    }
    return bestMove;
}