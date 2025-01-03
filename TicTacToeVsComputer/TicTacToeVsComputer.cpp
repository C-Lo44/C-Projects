#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const char HUMAN = 'O';
const char AI = 'X';
const char EMPTY = ' ';

// Game board
vector<vector<char>> board(3, vector<char>(3, EMPTY));

// Function to print the board with row and column numbers
void printBoard() {
    cout << "  0   1   2" << endl; // Column numbers
    for (int i = 0; i < 3; i++) {
        cout << i << " "; // Row numbers
        for (int j = 0; j < 3; j++) {
            cout << (board[i][j] == EMPTY ? '.' : board[i][j]);
            if (j < 2) cout << " | ";
        }
        cout << endl;
        if (i < 2) cout << "  ---------" << endl;
    }
}

// Check if three values are equal and not empty
bool equals3(char a, char b, char c) {
    return (a == b && b == c && a != EMPTY);
}

// Check for a winner or tie
string checkWinner() {
    // Horizontal
    for (int i = 0; i < 3; i++) {
        if (equals3(board[i][0], board[i][1], board[i][2]))
            return string(1, board[i][0]);
    }

    // Vertical
    for (int i = 0; i < 3; i++) {
        if (equals3(board[0][i], board[1][i], board[2][i]))
            return string(1, board[0][i]);
    }

    // Diagonal
    if (equals3(board[0][0], board[1][1], board[2][2]))
        return string(1, board[0][0]);
    if (equals3(board[2][0], board[1][1], board[0][2]))
        return string(1, board[2][0]);

    // Check for tie
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) return "None"; // Game not over
        }
    }

    return "tie";
}

// Minimax algorithm
int minimax(bool isMaximizing) {
    string result = checkWinner();
    if (result == "X") return 10;
    if (result == "O") return -10;
    if (result == "tie") return 0;

    if (isMaximizing) {
        int bestScore = numeric_limits<int>::min();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = AI;
                    int score = minimax(false);
                    board[i][j] = EMPTY;
                    bestScore = max(bestScore, score);
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = numeric_limits<int>::max();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = HUMAN;
                    int score = minimax(true);
                    board[i][j] = EMPTY;
                    bestScore = min(bestScore, score);
                }
            }
        }
        return bestScore;
    }
}

// Find the best move for the AI
pair<int, int> bestMove() {
    int bestScore = numeric_limits<int>::min();
    pair<int, int> move = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = AI;
                int score = minimax(false);
                board[i][j] = EMPTY;
                if (score > bestScore) {
                    bestScore = score;
                    move = {i, j};
                }
            }
        }
    }

    return move;
}

// Main function
int main() {
    cout << "Welcome to Tic Tac Toe!\n";
    printBoard();

    while (true) {
        // Human turn
        int x, y;
        cout << "Enter your move (row and column): ";
        cin >> x >> y;
        if (board[x][y] == EMPTY) {
            board[x][y] = HUMAN;
        } else {
            cout << "Invalid move! Try again.\n";
            continue;
        }

        printBoard();
        string result = checkWinner();
        if (result != "None") {
            if (result == "tie") {
                cout << "It's a tie!\n";
            } else {
                cout << result << " wins!\n";
            }
            break;
        }

        // AI turn
        cout << "AI is making a move...\n";
        pair<int, int> move = bestMove();
        board[move.first][move.second] = AI;

        printBoard();
        result = checkWinner();
        if (result != "None") {
            if (result == "tie") {
                cout << "It's a tie!\n";
            } else {
                cout << result << " wins!\n";
            }
            break;
        }
    }

    return 0;
}
