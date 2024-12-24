/*
#include"engine.h"

int minimax(Chess& localchess, int depth, int alpha, int beta, bool isMaximizing) {
    if (depth == 0) return localchess.evaluate();
    vector <string> moves = findAllMoves(localchess);
    if (moves.empty()) return isMaximizing ? -1e9 : 1e9;
    if (isMaximizing) {
        int bestScore = -1e9;
        for (string move : moves) {
            Chess newchess = localchess;
            newchess.makeMove(move);
            bestScore = max(bestScore, minimax(newchess, depth - 1, alpha, beta, false));
            alpha = max(alpha, bestScore);
            if (beta <= alpha) break;
        }
        return bestScore;
    } 
    else {
        int bestScore = 1e9;
        for (string move : moves) {
            Chess newchess = localchess;
            newchess.makeMove(move);
            bestScore = min(bestScore, minimax(newchess, depth - 1, alpha, beta, true));
            beta = min(beta, bestScore);
            if (beta <= alpha) break;
        }
        return bestScore;
    }
}

string findBestMove(Chess& localchess) {
    vector <string> moves = findAllMoves(localchess);
    int bestScore = -1e9;
    string bestMove;
    for (string move : moves) {
        Chess newchess = localchess;
        newchess.makeMove(move);
        int score = minimax(newchess, 3, -1e9, 1e9, false);
        if (score > bestScore) {
            bestScore = score;
            bestMove = move;
        }
    }
    return bestMove;
}
*/