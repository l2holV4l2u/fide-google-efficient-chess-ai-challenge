#include "engine.h"

bool side; // 0 for black, 1 for white

string algebraicNotation(int square) {
    return string(1, 'a' + square % 8) + string(1, '1' + square / 8);
}

bool outOfBound(int square) {
    return square < 0 || square > 63;
}

bool pushValid(int current, int newSquare, vector<string>& moves, const Board& board) { // Use reference for moves and board
    if (outOfBound(newSquare)) {
        return true; // Stop further moves in this direction
    }
    char target = board.sn[newSquare];
    if (target == ' ') { // Empty square
        moves.emplace_back(algebraicNotation(current) + algebraicNotation(newSquare));
        return false; // Continue in this direction
    }
    else if (islower(target) != islower(board.sn[current])) { // Capture
        moves.emplace_back(algebraicNotation(current) + 'x' + algebraicNotation(newSquare));
    }
    return true; // Stop further moves
}

void findRookMoves(int square, const Board& board, vector<string>& moves) {
    int directions[4] = {1, -1, 8, -8};
    for (int k = 0; k < 4; ++k) {
        for (int j = 1; j <= 8; ++j) {
            if (pushValid(square, square + j * directions[k], moves, board)) {
                break; // Stop if the path is blocked
            }
        }
    }
}

void findKnightMoves(int square, const Board& board, vector<string>& moves) {
    int knightXOffsets[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int knightYOffsets[8] = {8, 16, 16, 8, -8, -16, -16, -8};
    for (int k = 0; k < 8; ++k) {
        if ((square + knightXOffsets[k])/8 == square/8  && (square + knightYOffsets[k])%8 == square%8) {
            pushValid(square, square + knightXOffsets[k] + knightYOffsets[k], moves, board);
        }
    }
}

void findPawnMoves(int square, const Board& board, vector<string>& moves) {
    int forward = 8 * (side ? 1 : -1);
    pushValid(square, square + forward, moves, board); // Forward move
    if ((!side && square / 8 == 6) || (side && square / 8 == 1)) { // Initial double move
        pushValid(square, square + 2 * forward, moves, board);
    }
}

void findBishopMoves(int square, const Board& board, vector<string>& moves) {
    int directions[4] = {9, 7, -9, -7};
    for (int k = 0; k < 4; ++k) {
        for (int j = 1; j <= 8; ++j) {
            if (pushValid(square, square + j * directions[k], moves, board)) {
                break; // Stop if the path is blocked
            }
        }
    }
}

void findQueenMoves(int square, const Board& board, vector<string>& moves) {
    findRookMoves(square, board, moves);
    findBishopMoves(square, board, moves);
}

void findKingMoves(int square, const Board& board, vector<string>& moves) {
    int directions[8] = {1, -1, 8, -8, 9, 7, -9, -7};
    for (int k = 0; k < 8; ++k) {
        pushValid(square, square + directions[k], moves, board);
    }
}

vector <string> findMoves(Board& board) {
    vector <string> moves;
    side = board.turn;
    for (int i=0;i<board.sn.length();i++) {
        if (board.sn[i] == ' ' || isupper(board.sn[i]) != side) continue; // Skip empty squares & opponent's pieces
        char piece = tolower(board.sn[i]);
        if(piece == 'n') findKnightMoves(i, board, moves);
        else if(piece == 'p') findPawnMoves(i, board, moves);
        else if(piece == 'b') findBishopMoves(i, board, moves);
        else if(piece == 'r') findRookMoves(i, board, moves);
        else if(piece == 'q') findQueenMoves(i, board, moves);
        else if(piece == 'k') findKingMoves(i, board, moves);
    }
    return moves;
}