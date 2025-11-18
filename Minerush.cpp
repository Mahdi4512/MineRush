#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
//hello
const int MAX_SIZE = 20;


bool safeInput(int &x) {
    if (!(cin >> x)) {
        cin.clear();
        cin.ignore(1000, '\n');
        return false;
    }
    return true;
}

bool inBounds(int r, int c, int rows, int cols) {
    return r >= 0 && r < rows && c >= 0 && c < cols;
}


void printField(int rows, int cols,
                int field[][MAX_SIZE],
                bool reveal[][MAX_SIZE],
                bool flagArr[][MAX_SIZE],
                bool showMines = false) {

    cout << "\n    ";
    for (int j = 0; j < cols; j++) cout << j + 1 << " ";
    cout << "\n   ";
    for (int j = 0; j < cols; j++) cout << "--";
    cout << "\n";

    for (int i = 0; i < rows; i++) {
        if (i + 1 < 10) cout << " " << i + 1 << "| ";
        else cout << i + 1 << "| ";

        for (int j = 0; j < cols; j++) {

            if (reveal[i][j]) {
                if (field[i][j] == -1) cout << "M ";
                else cout << field[i][j] << " ";
            }
            else if (flagArr[i][j]) {
                cout << "F ";
            }
            else if (showMines && field[i][j] == -1) {
                cout << "M ";
            }
            else cout << "* ";
        }
        cout << endl;
    }
}


void placeMines(int rows, int cols, int mines, int field[][MAX_SIZE]) {
    int placed = 0;
    while (placed < mines) {
        int r = rand() % rows;
        int c = rand() % cols;
        if (field[r][c] != -1) {
            field[r][c] = -1;
            placed++;
        }
    }
}


void calculateNumbers(int rows, int cols, int field[][MAX_SIZE]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            if (field[i][j] == -1) continue;

            int count = 0;
            for (int dr = -1; dr <= 1; dr++) {
                for (int dc = -1; dc <= 1; dc++) {
                    if (dr == 0 && dc == 0) continue;
                    int nr = i + dr, nc = j + dc;
                    if (inBounds(nr, nc, rows, cols) && field[nr][nc] == -1)
                        count++;
                }
            }
            field[i][j] = count;
        }
    }
}


void floodReveal(int r, int c,
                 int rows, int cols,
                 int field[][MAX_SIZE],
                 bool reveal[][MAX_SIZE],
                 bool flagArr[][MAX_SIZE]) {

    if (!inBounds(r, c, rows, cols)) return;
    if (reveal[r][c]) return;
    if (flagArr[r][c]) return;

    reveal[r][c] = true;

    if (field[r][c] == 0) {
        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                if (dr == 0 && dc == 0) continue;
                floodReveal(r + dr, c + dc, rows, cols, field, reveal, flagArr);
            }
        }
    }
}


bool checkWin(int rows, int cols,
              int field[][MAX_SIZE],
              bool reveal[][MAX_SIZE]) {

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (field[i][j] != -1 && !reveal[i][j])
                return false;
    return true;
}


int main() {
    srand(time(0));

    bool playAgain = true;

    while (playAgain) {

        int rows, cols, mines, mode;

        cout << "Enter rows (1-" << MAX_SIZE << "): ";
        while (!safeInput(rows) || rows < 1 || rows > MAX_SIZE)
            cout << "Invalid input, try again: ";

        cout << "Enter cols (1-" << MAX_SIZE << "): ";
        while (!safeInput(cols) || cols < 1 || cols > MAX_SIZE)
            cout << "Invalid input, try again: ";

        cout << "Enter number of mines: ";
        while (!safeInput(mines) || mines < 1 || mines >= rows * cols)
            cout << "Invalid input, try again: ";

        cout << "Enter mode (1 = Single, 2 = Multi): ";
        while (!safeInput(mode) || (mode != 1 && mode != 2))
            cout << "Invalid input, try again: ";

        int field[MAX_SIZE][MAX_SIZE] = {0};
        bool reveal[MAX_SIZE][MAX_SIZE] = {0};
        bool flagArr[MAX_SIZE][MAX_SIZE] = {0};

        placeMines(rows, cols, mines, field);
        calculateNumbers(rows, cols, field);

        bool gameOver = false;
        int currentPlayer = 1;

        printField(rows, cols, field, reveal, flagArr);

        while (!gameOver) {
            cout << "\n==========\n";
            if (mode == 2) 
                cout << "Player " << currentPlayer << "'s turn\n";

            int action;
            cout << "Choose action (1 = reveal, 2 = flag): ";
            while (!safeInput(action) || (action != 1 && action != 2))
                cout << "Invalid choice, try again: ";

            int r, c;
            cout << "Enter row and col: ";
            while (!safeInput(r) || !safeInput(c) || !inBounds(r - 1, c - 1, rows, cols))
                cout << "Invalid position, try again: ";
            r--, c--;

            if (action == 1) { // Reveal
                if (flagArr[r][c]) {
                    cout << "Cell is flagged!\n";
                    continue;
                }

                if (field[r][c] == -1) {
                    cout << "\n Boom! Mine hit!\n";
                    printField(rows, cols, field, reveal, flagArr, true);
                    gameOver = true;
                    break;
                }

                floodReveal(r, c, rows, cols, field, reveal, flagArr);
                printField(rows, cols, field, reveal, flagArr);

                if (checkWin(rows, cols, field, reveal)) {
                    cout << "\n🎉 You win!\n";
                    gameOver = true;
                }
            }

            else { // Flag
                if (reveal[r][c]) {
                    cout << "Cell already revealed!\n";
                    continue;
                }

                flagArr[r][c] = !flagArr[r][c];
                printField(rows, cols, field, reveal, flagArr);
            }

            if (!gameOver && mode == 2)
                currentPlayer = (currentPlayer == 1 ? 2 : 1);
        }

        char again;
        cout << "\nPlay again? (y/n): ";
        cin >> again;
        playAgain = (again == 'y' || again == 'Y');
    }

    cout << "\nThanks for playing!\n";
    return 0;
}
