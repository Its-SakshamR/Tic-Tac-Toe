#include<bits/stdc++.h>
using namespace std;

struct Move{
    int row, col;
};

const char player = 'x', machine = 'o';

void drawBoard(char board[3][3]){
    cout << "-------------\n";
    for (int i = 0 ; i < 3 ; i++){
        cout << "| ";
        for (int j = 0 ; j < 3 ; j++){
            cout << board[i][j] << " | ";
        }
        cout << "\n-------------\n";
    }
}

bool ifMovesLeft(char board[3][3]){
    for (int i = 0 ; i < 3 ; i++){
        for (int j = 0 ; j < 3 ; j++){
            if (board[i][j] == '_') return true;
        }
    }
    return false;
}

int isWin(char board[3][3]){

    for (int row = 0 ; row < 3 ; row++){
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]){
            if (board[row][0] == player) return 1;
            else if (board[row][0] == machine)return -1;
        }
    }

    for (int col = 0 ; col < 3 ; col++){
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]){
            if (board[0][col] == player) return 1;
            else if (board[0][col] == machine) return -1;
        }
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]){
        if (board[0][0] == player) return 1;
        else if (board[0][0] == machine) return -1;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]){
        if (board[0][2] == player) return 1;
        else if (board[0][2] == machine) return -1;
    }

    return 0;
}

int minimax(char board[3][3], bool isMax)
{
    int x = isWin(board);

    if (x == 1 || x == -1) return x;

    if (ifMovesLeft(board) == false)
        return 0;

    // If this is maximizer's move 
    if (isMax){
        int best = INT_MIN;

        for (int i = 0 ; i < 3 ; i++){
            for (int j = 0 ; j < 3 ; j++){
                if (board[i][j] == '_'){
                    board[i][j] = player;
                    best = max(best, minimax(board, !isMax) );      // Recursively calling minimax
                    board[i][j] = '_';        // Set the board as before
                }
            }
        }
        return best;
    }

    // If this is minimizer's move 
    else{
        int best = INT_MAX;

        for (int i = 0 ; i < 3 ; i++){
            for (int j = 0 ; j < 3 ; j++){
                if (board[i][j] == '_'){
                    board[i][j] = machine;
                    best = min(best, minimax(board, !isMax));
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
}

Move BestMove(char board[3][3])
{
    int bestVal = INT_MAX;
    Move bestmove;
    bestmove.row = -1;
    bestmove.col = -1;

    // We will check minimax for every empty cell.
    for (int i = 0 ; i < 3 ; i++){
        for (int j = 0 ; j < 3 ; j++){
            if (board[i][j] == '_'){

                board[i][j] = machine;
                int moveVal = minimax(board, true);

                board[i][j] = '_';
                if (moveVal < bestVal){ 
                    bestmove.row = i; 
                    bestmove.col = j; 
                    bestVal = moveVal; 
                }
            }
        }
    }
  
    return bestmove; 
} 

int main() 
{ 
    char board[3][3] = {{ '_', '_', '_' }, 
                        { '_', '_', '_' }, 
                        { '_', '_', '_' }};

    int k;

    cout << "Enter 0 if you want to go first, else 1: ";

    cin >> k;

    for(int turn = k ; turn < k+9 ; turn++){
        drawBoard(board);

        if(turn%2 == 0){
            Move newmove;
            int a, b;
            while(true) {           // Until valid input received
                cout << "Your Turn, enter row col as \"a a\" : ";
                cin >> a >> b;
                newmove.row = a-1;
                newmove.col = b-1;

                if (board[newmove.row][newmove.col] != '_' || newmove.row < 0 || newmove.row > 2 || newmove.col < 0 || newmove.col > 2) { 
                    cout << "This is an invalid move.\n"; 
                }

                else break; // Valid input received
            }

            board[newmove.row][newmove.col] = player;

            if(isWin(board) != 0){
                drawBoard(board);
                cout << "Congratulations, you won!\n";
                return 0;
            }
        }

        else{
            cout<<"Computer's turn\n";
            Move bestmove = BestMove(board);
            board[bestmove.row][bestmove.col] = machine;

            if(isWin(board) != 0){
                drawBoard(board);
                cout << "Computer won!\n";
                return 0;
            }
        }
    }
    drawBoard(board);
    cout<<"It's a draw\n";
    return 0; 
} 