#include <bits/stdc++.h>
using namespace std;

const int row = 3;
const int col = 3;
const int inf = (int)1e3;

char board[row][col];
vector <pair <int,int> > winningState[8];

void printBoard() {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (j == 0) cout << board[i][j];
            else cout << '\t' << board[i][j];
        }
        cout << "\n\n\n";
    }
}
void setWinningState() {
    winningState[0] = {{0, 0}, {0, 1}, {0, 2}};
    winningState[1] = {{1, 0}, {1, 1}, {1, 2}};
    winningState[2] = {{2, 0}, {2, 1}, {2, 2}};
    winningState[3] = {{0, 0}, {1, 0}, {2, 0}};
    winningState[4] = {{0, 1}, {1, 1}, {2, 1}};
    winningState[5] = {{0, 2}, {1, 2}, {2, 2}};
    winningState[6] = {{0, 0}, {1, 1}, {2, 2}};
    winningState[7] = {{0, 2}, {1, 1}, {2, 0}};
}
set <pair <int,int> > getAvailableCells(char tempBoard[row][col]) {
    set <pair <int,int> > availableCells;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (tempBoard[i][j] == '*') availableCells.insert(make_pair(i, j));
        }
    }
    return availableCells;
}
int checkWinningState(char tempBoard[row][col]) {
    for (int i = 0; i < 8; i++) {
        string current = "";
        for (auto state: winningState[i]) {
            current += tempBoard[state.first][state.second];
        }
        if (current == "HHH") return -inf;
        if (current == "AAA") return inf;
    }
    return 0;
}
int miniMax(char tempBoard[row][col], bool maximize) {
    int currentState = checkWinningState(tempBoard);
    if (currentState != 0) return currentState;
    int emptyCell = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (tempBoard[i][j] == '*') emptyCell++;
        }
    }
    if (emptyCell == 0) return 0;
    if (maximize) {
        int bestScore = -inf;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (tempBoard[i][j] == '*') {
                    tempBoard[i][j] = 'A';
                    bestScore = max(bestScore, miniMax(tempBoard, false));
                    tempBoard[i][j] = '*';
                }
            }
        }
        return bestScore;
    }
    else {
        int bestScore = inf;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (tempBoard[i][j] == '*') {
                    tempBoard[i][j] = 'H';
                    bestScore = min(bestScore, miniMax(tempBoard, true));
                    tempBoard[i][j] = '*';
                }
            }
        }
        return bestScore;
    }
}
pair <int,int> findBestPos() {
    int l = -1, r = -1, bestScore = -inf;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (board[i][j] == '*') {
                board[i][j] = 'A';
                int curScore = miniMax(board, false);
                if (curScore > bestScore) {
                    bestScore = curScore;
                    l = i, r = j;
                }
                board[i][j] = '*';
            }
        }
    }
    return make_pair(l, r);
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    setWinningState();
    memset(board, '*', sizeof(board));
    printBoard();
    int totalMove = 9;
    while (totalMove--) {
        int who = checkWinningState(board);
        if (who == -inf) return cout << "Human Wins!!!" << endl, 0;
        else if (who == inf) return cout << "AI Wins!!!" << endl, 0;
        if (totalMove % 2 == 0) {
            set <pair <int,int> > cells = getAvailableCells(board);
            cout << "Your turn & available cells are: \n";
            for (auto cell: cells) cout << cell.first << " " << cell.second << "\n";
            int r, c;
            while (cin >> r >> c) {
                if (cells.find({r, c}) != cells.end()) break;
                else cout << "invalid cell, choose again" << "\n";
            }
            board[r][c] = 'H';
            system("CLS");
        }
        else {
            pair <int,int> pos = findBestPos();
            board[pos.first][pos.second] = 'A';
        }
        printBoard();
    }
    cout << "It's a draw!!!" << "\n";
    return 0;
}


