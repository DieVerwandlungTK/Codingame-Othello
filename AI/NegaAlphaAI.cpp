#include "NegaAlphaAI.hpp"

NegaAlphaAI::NegaAlphaAI(Color AIColor, int depth, std::function<int(uint64_t, uint64_t, Color)> eval): AIBase(AIColor, eval), depth(depth){
}

int NegaAlphaAI::search(uint64_t blackPieces, uint64_t whitePieces, int depth, Color color, bool passed, int alpha, int beta){
    if(depth == 0){
        return eval(blackPieces, whitePieces, AIColor)*(color == AIColor ? 1 : -1);
    }

    std::vector<uint64_t> legalMoves = board.getPopPositions(board.getLegalMoves(color));

    if(legalMoves.empty()){
        if(passed){
            return eval(blackPieces, whitePieces, AIColor);
        }
        return -search(blackPieces, whitePieces, depth-1, Color(color^1), true, -beta, -alpha);
    }
    else{
        OthelloBoard tmp;
        for(uint64_t move: legalMoves){
            tmp.setBoard(blackPieces, whitePieces);
            tmp.makeMove(move, color);
            int score = -search(tmp.getBlackPieces(), tmp.getWhitePieces(), depth-1, Color(color^1), false, -beta, -alpha);
            if(score>=beta){
                return score;
            }
            alpha = std::max(alpha, score);
        }
        return alpha;
    }
}

uint64_t NegaAlphaAI::getMove(){
    int alpha = INT32_MIN, beta = INT32_MAX;
    uint64_t bestMove = 0;
    std::vector<uint64_t> legalMoves = board.getPopPositions(board.getLegalMoves(AIColor));
    OthelloBoard tmp;
    for(uint64_t move: legalMoves){
        tmp.setBoard(board.getBlackPieces(), board.getWhitePieces());
        tmp.makeMove(move, AIColor);
        int score = -search(tmp.getBlackPieces(), tmp.getWhitePieces(), depth-1, Color(AIColor^1), false, -beta, -alpha);
        if(score>alpha){
            alpha = score;
            bestMove = move;
        }
    }
    return bestMove;
}