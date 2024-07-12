#include <bits/stdc++.h>
using namespace std;

struct Move {
    int row, col;
};

class TicTacToe {
private:
    char board[3][3];
    const char player = 'x', machine = 'o';

    void drawBoard() const {
        cout << "-------------\n";
        for (int i = 0; i < 3; i++) {
            cout << "| ";
            for (int j = 0; j < 3; j++) {
                cout << board[i][j] << " | ";
            }
            cout << "\n-------------\n";
        }
    }

    bool ifMovesLeft() const {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '_') return true;
            }
        }
        return false;
    }

    int isWin() const {
        for (int row = 0; row < 3; row++) {
            if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
                if (board[row][0] == player) return 1;
                else if (board[row][0] == machine) return -1;
            }
        }

        for (int col = 0; col < 3; col++) {
            if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
                if (board[0][col] == player) return 1;
                else if (board[0][col] == machine) return -1;
            }
        }

        if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            if (board[0][0] == player) return 1;
            else if (board[0][0] == machine) return -1;
        }

        if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            if (board[0][2] == player) return 1;
            else if (board[0][2] == machine) return -1;
        }

        return 0;
    }

    int minimax(bool isMax) {
        int score = isWin();

        if (score == 1 || score == -1) return score;

        if (!ifMovesLeft()) return 0;

        if (isMax) {
            int best = INT_MIN;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == '_') {
                        board[i][j] = player;
                        best = max(best, minimax(!isMax));
                        board[i][j] = '_';
                    }
                }
            }
            return best;
        } else {
            int best = INT_MAX;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == '_') {
                        board[i][j] = machine;
                        best = min(best, minimax(!isMax));
                        board[i][j] = '_';
                    }
                }
            }
            return best;
        }
    }

    Move bestMove() {
        int bestVal = INT_MAX;
        Move bestMove = {-1, -1};

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = machine;
                    int moveVal = minimax(true);
                    board[i][j] = '_';
                    if (moveVal < bestVal) {
                        bestMove.row = i;
                        bestMove.col = j;
                        bestVal = moveVal;
                    }
                }
            }
        }

        return bestMove;
    }

public:
    TicTacToe() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = '_';
            }
        }
    }

    void playGame(int n) {
        if(n == 2){
            int k = 0;
            while(k != 1 && k!= 2){
                cout << "Enter 1 if you want to go first, else 2: ";
                cin >> k;
            }
            k--;
            for (int turn = k; turn < k + 9; turn++) {
                drawBoard();

                if (turn % 2 == 0) {
                    Move newMove;
                    int a, b;
                    while (true) {
                        cout << "Your Turn, enter row col as \"a a\": ";
                        cin >> a >> b;
                        newMove.row = a - 1;
                        newMove.col = b - 1;

                        if (board[newMove.row][newMove.col] != '_' || newMove.row < 0 || newMove.row > 2 || newMove.col < 0 || newMove.col > 2) {
                            cout << "This is an invalid move.\n";
                        } else {
                            break;
                        }
                    }
                    board[newMove.row][newMove.col] = player;

                    if (isWin() != 0) {
                        drawBoard();
                        cout << "Congratulations, you won!\n";
                        return;
                    }
                } else {
                    cout << "Computer's turn\n";
                    Move bestmove = bestMove();
                    board[bestmove.row][bestmove.col] = machine;

                    if (isWin() != 0) {
                        drawBoard();
                        cout << "Computer won!\n";
                        return;
                    }
                }
            }

            drawBoard();
            cout << "It's a draw\n";
        }

        else{
            for(int turn = 0 ; turn < 9 ; turn++){
                 drawBoard();

                if (turn % 2 == 0) {
                    Move newMove;
                    int a, b;
                    while (true) {
                        cout << "Player 1's Turn, enter row col as \"a a\": ";
                        cin >> a >> b;
                        newMove.row = a - 1;
                        newMove.col = b - 1;

                        if (board[newMove.row][newMove.col] != '_' || newMove.row < 0 || newMove.row > 2 || newMove.col < 0 || newMove.col > 2) {
                            cout << "This is an invalid move.\n";
                        } else {
                            break;
                        }
                    }
                    board[newMove.row][newMove.col] = player;

                    if (isWin() != 0) {
                        drawBoard();
                        cout << "Player 1 won!\n";
                        return;
                    }
                } else {
                    Move newMove;
                    int a, b;
                    while (true) {
                        cout << "Player 2's Turn, enter row col as \"a a\": ";
                        cin >> a >> b;
                        newMove.row = a - 1;
                        newMove.col = b - 1;

                        if (board[newMove.row][newMove.col] != '_' || newMove.row < 0 || newMove.row > 2 || newMove.col < 0 || newMove.col > 2) {
                            cout << "This is an invalid move.\n";
                        } else {
                            break;
                        }
                    }
                    board[newMove.row][newMove.col] = machine;

                    if (isWin() != 0) {
                        drawBoard();
                        cout << "Player 2 won!\n";
                        return;
                    }
                }
            }
        }
    }
};

int main() {
    int n;
    cout << "Enter 1 for P vs P or 2 for P vs C: ";
    cin >> n;
    TicTacToe game;
    game.playGame(n);
    return 0;
}
