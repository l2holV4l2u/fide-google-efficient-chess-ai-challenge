#include "engine.h"

bool side; // 0 for black, 1 for white
int kingrow, kingcol;
vector <string> moves;
Chess chess("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

string algebraicNotation(int row, int col) {
    return string(1, 'a' + col) + string(1, '1' + row);
}

bool outOfBound(int row, int col) {
    return row < 0 || row >= 8 || col < 0 || col >= 8;
}

bool isOpponent(int row, int col, char piece) {
    return !outOfBound(row, col) && tolower(chess.board[row][col]) == piece && isupper(chess.board[row][col]) != side;
}

bool checkKingValidPosition(int row, int col) {
    // checked by opponent's pawn
    if (isOpponent(row + (side ? 1 : -1), col - 1, 'p')) return false; // left pawn
    if (isOpponent(row + (side ? 1 : -1), col + 1, 'p')) return false; // right pawn
    
    // checked by opponent's knight
    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            if (isOpponent(row + 2 * i, col + j, 'n')) return false;
            if (isOpponent(row + i, col + 2 * j, 'n')) return false;
        }
    }

    // checked by opponent's bishop or rook or queen
    for (int i = -1; i <= 1 ; i += 2){
        for (int j = -1; j <= 1; j += 2){
            for (int k = 1; k < 8; k++){
                if (isOpponent(row + k * i, col + k * j, 'b') || isOpponent(row + k * i, col + k * j, 'q')) return false;
                if (chess.board[row + k * i][col + k * j] != ' ') break;
            }
        }
    }
    int direction[4] = {-1, 1, 0, 0};
    for (int i = 0; i < 4 ; i ++){
        for (int j = 1; j < 8; j++){
            if (isOpponent(row + j * direction[i], col + j * direction[3-i], 'r') || isOpponent(row + j * direction[i], col + j * direction[3-i], 'q')) return false;
            if (chess.board[row + j * direction[i]][col + j * direction[3-i]] != ' ') break;
        }
    }

    // checked by opponent's king
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            if (isOpponent(row + i, col + j, 'k')) return false;
        }
    }
    
    return true;
}

bool moveAndCheckKing(int currow, int curcol, int nextrow, int nextcol){
    char target = chess.board[nextrow][nextcol];
    bool flag = 0;
    if (tolower(chess.board[currow][curcol]) == 'k') flag = 1, kingrow = nextrow, kingcol = nextcol;
    chess.board[nextrow][nextcol] = chess.board[currow][curcol];
    chess.board[currow][curcol] = ' ';
    bool result = checkKingValidPosition(kingrow, kingcol);
    chess.board[currow][curcol] = chess.board[nextrow][nextcol];
    chess.board[nextrow][nextcol] = target;
    if (flag) kingrow = currow, kingcol = curcol;
    return result;
}

// works for every pieces except pawn
bool isValid(int currow, int curcol, int nextrow, int nextcol) {
    if (outOfBound(nextrow, nextcol)) return true; // Stop further moves in this direction
    char target = chess.board[nextrow][nextcol];
    if (target == ' ' || isupper(target) != side) { // Empty square or opponent's piece
        if (moveAndCheckKing(currow, curcol, nextrow, nextcol)) moves.push_back(algebraicNotation(currow, curcol) + algebraicNotation(nextrow, nextcol));
        return target != ' '; // Stop further moves if opponent's piece
    }
    return true; // Stop further moves
}

void findKnightMoves(int row, int col) {
    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            isValid(row, col, row + 2 * i, col + 1 * j);
            isValid(row, col, row + 1 * i, col + 2 * j);
        }
    }
}

void findPawnMoves(int row, int col) {
    int forward = (side ? 1 : -1);
    if (!outOfBound(row + forward, col - 1) && chess.board[row + forward][col - 1] != ' ' && isupper(chess.board[row + forward][col - 1]) != side && moveAndCheckKing(row, col, row + forward, col - 1)) { // Capture left
        moves.push_back(algebraicNotation(row, col) + algebraicNotation(row + forward, col - 1) + ((side && row == 6) || (!side && row == 1) ? 'q' : ' '));
    }
    if (!outOfBound(row + forward, col + 1) && chess.board[row + forward][col + 1] != ' ' && isupper(chess.board[row + forward][col + 1]) != side && moveAndCheckKing(row, col, row + forward, col + 1)) { // Capture right
        moves.push_back(algebraicNotation(row, col) + algebraicNotation(row + forward, col + 1) + ((side && row == 6) || (!side && row == 1) ? 'q' : ' '));
    }
    if (chess.board[row + forward][col] == ' ' && moveAndCheckKing(row, col, row + forward, col)) { // Move forward
        moves.push_back(algebraicNotation(row, col) + algebraicNotation(row + forward, col) + ((side && row == 6) || (!side && row == 1) ? 'q' : ' '));
    }
    if (((!side && row == 6) || (side && row == 1)) && chess.board[row + forward][col] == ' ' && chess.board[row + 2 * forward][col] == ' ' && moveAndCheckKing(row, col, row + 2 * forward, col)) { // Initial double move
        moves.push_back(algebraicNotation(row, col) + algebraicNotation(row + 2 * forward, col));
    }
}

void findBishopMoves(int row, int col) {
    for (int i = -1; i <= 1 ; i += 2){
        for (int j = -1; j <= 1; j += 2){
            for (int k = 1; k < 8; k++){
                if (isValid(row, col, row + k * i, col + k * j)) break;
            }
        }
    }
}

void findRookMoves(int row, int col) {
    int direction[4] = {-1, 1, 0, 0};
    for (int i = 0; i < 4 ; i ++){
        for (int j = 1; j < 8; j++){
            if (isValid(row, col, row + j * direction[i], col + j * direction[3-i])) break;
        }
    }
}

void findQueenMoves(int row, int col) {
    findRookMoves(row, col);
    findBishopMoves(row, col);
}

void findKingMoves(int row, int col) {
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            isValid(row, col, row + i, col + j);         
        }
    }
}

// gives all possible moves for the current side in UCI notation
vector <string> findAllMoves(Chess& localchess) {
    moves.clear();
    chess = localchess;
    side = chess.turn;
    kingrow = localchess.king[side][0], kingcol = localchess.king[side][1];
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            if (chess.board[i][j] == ' ' || isupper(chess.board[i][j]) != side) continue; // Skip empty squares & opponent's pieces
            char piece = tolower(chess.board[i][j]);
            if(piece == 'n') findKnightMoves(i, j);
            else if(piece == 'p') findPawnMoves(i, j);
            else if(piece == 'b') findBishopMoves(i, j);
            else if(piece == 'r') findRookMoves(i, j);
            else if(piece == 'q') findQueenMoves(i, j);
            else if(piece == 'k') findKingMoves(i, j);
        }
    }
    return moves;
}