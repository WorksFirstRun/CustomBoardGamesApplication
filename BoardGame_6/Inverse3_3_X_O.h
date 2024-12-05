#ifndef _5X5X_O_H
#define _5X5X_O_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <string>
template <typename T> class ThreeByThree_Board;
template <typename T> class ThreeByThree_HumanPlayer;
template <typename T> class ThreeByThree_RandomPlayer;

//================= Board Class =================
template <typename T>
class ThreeByThree_Board : public Board<T> {
private:
    int countThreeInARow(T symbol);
    bool isValidMove(int x, int y, T symbol);

public:
    ThreeByThree_Board() {
        this->rows = this->columns = 3;
        this->board = new T*[this->rows];
        for (int i = 0; i < this->rows; i++) {
            this->board[i] = new T[this->columns];
            for (int j = 0; j < this->columns; j++) {
                this->board[i][j] = '.';
            }
        }
        this->n_moves = 0;
    }

    // Core game functions
    bool update_board(int x, int y, T symbol) override {
        if (isValidMove(x,y,symbol)) {
            if (symbol == '.'){
                this->n_moves--;
                this->board[x][y] = '.';
            }
            else {
                this->n_moves++;
                this->board[x][y] = symbol;
            }
            return true;
        }
        return false;
    }

    void display_board() override {
        cout << "\n";
        for (int i = 0; i < this->rows; i++) {
            cout << " | ";
            for (int j = 0; j < this->columns; j++) {
                cout << this->board[i][j] << " | ";
            }
            cout << "\n";
            if (i < this->rows - 1) {
                cout << "-------------\n";
            }
        }
        cout << endl;
    }
    bool is_win() override {
        return countThreeInARow('X') > 0 || countThreeInARow('O') > 0;
    }

    bool is_draw() override {
        if (game_is_over()) {
            int count_X = countThreeInARow('X');
            int count_O = countThreeInARow('O');
            return count_X == count_O;
        }
        return false;
    }
    string whoWon(const string& player1Name, const string& player2Name) {
        int count_X = countThreeInARow('X');
        int count_O = countThreeInARow('O');

        if (game_is_over()) {
            if (count_X > count_O) {
                return player2Name;
            } else if (count_O > count_X) {
                return player1Name;
            }
        }
        return "";
    }
    bool game_is_over() override {
        return countThreeInARow('X') > 0 || countThreeInARow('O') > 0 || this->n_moves == 9;
    }


    T** GetBoardState() {
        return this->board;
    }


};

//================= Human Player Class =================
template <typename T>
class ThreeByThree_HumanPlayer : public Player<T> {
public:

    ThreeByThree_HumanPlayer(string n,T symbol) : Player<T>(n,symbol){}

    void getmove(int& x, int& y) override {
        cout << "\nPlayer " << this->name << "'s turn (" << this->symbol << ")" << endl;
        cout << "Please enter your move x and y (0 to 2) separated by spaces: ";

        cin >> x >> y;

    }
};


//================= Random Player Class =================
template <typename T>
class ThreeByThree_RandomPlayer : public Player<T> {
private:
    int dimension;

public:
    ThreeByThree_RandomPlayer(T symbol) : Player<T>("Random Computer Player", symbol) {
        dimension = 3;
        srand(static_cast<unsigned int>(time(0)));
    }

    void getmove(int& x, int& y) override {
        x = rand() % dimension;
        y = rand() % dimension;
        while (!this->boardPtr->update_board(x, y, this->symbol)) {
            x = rand() % dimension;
            y = rand() % dimension;
        }
        this->boardPtr->update_board(x, y, '.');
    }
};



//================= Helper Function Implementations =================
template <typename T>
int ThreeByThree_Board<T>::countThreeInARow(T symbol) {
    int count = 0;

    // Check horizontal three-in-a-row
    for (int i = 0; i < this->rows; i++) {
        for (int j = 1; j < this->columns - 1; j++) {
            if (this->board[i][j] == symbol &&
                this->board[i][j-1] == symbol &&
                this->board[i][j+1] == symbol) {
                count++;
            }
        }
    }

    // Check vertical three-in-a-row
    for (int i = 1; i < this->rows - 1; i++) {
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] == symbol &&
                this->board[i-1][j] == symbol &&
                this->board[i+1][j] == symbol) {
                count++;
            }
        }
    }

    // Check diagonal (top-left to bottom-right)
    for (int i = 1; i < this->rows - 1; i++) {
        for (int j = 1; j < this->columns - 1; j++) {
            if (this->board[i][j] == symbol &&
                this->board[i-1][j-1] == symbol &&
                this->board[i+1][j+1] == symbol) {
                count++;
            }
        }
    }

    // Check diagonal (top-right to bottom-left)
    for (int i = 1; i < this->rows - 1; i++) {
        for (int j = 1; j < this->columns - 1; j++) {
            if (this->board[i][j] == symbol &&
                this->board[i-1][j+1] == symbol &&
                this->board[i+1][j-1] == symbol) {
                count++;
            }
        }
    }

    return count;
}

template <typename T>
bool ThreeByThree_Board<T>::isValidMove(int x, int y, T symbol) {
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns) {
        return false;
    }

    if (symbol != '.') {
        return this->board[x][y] == '.';
    }

    return this->board[x][y] != '.';
}



void RunBoardGame(){
    int choice;

    Board<char> * board = new ThreeByThree_Board<char>();
    Player<char> * players[2];

    string player1,player2;


    cout << "Five by Five XO GameBoard3 \n";

    // Set up player 1
    cout << "Enter Player 1 name (symbol is X): ";
    cin >> player1;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. Smart Computer (AI)\n";
    cin >> choice;

    switch(choice){
        case 1:
            players[0] = new ThreeByThree_HumanPlayer<char>(player1,'X');
            break;
        case 2:
            players[0] = new ThreeByThree_RandomPlayer<char>('X');
            players[0]->setBoard(board);
            break;
        case 3:

        default:
            break;
    }


    cout << "Enter Player 2 name (symbol is O): ";
    cin >> player2;
    cout << "Choose Player O type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. Smart Computer (AI)\n";
    cin >> choice;

    switch(choice){
        case 1:
            players[1] = new ThreeByThree_HumanPlayer<char>(player2,'O');
            break;
        case 2:
            players[1] = new ThreeByThree_RandomPlayer<char>('O');
            players[1]->setBoard(board);
            break;
        case 3:

            break;
        default:
            break;
    }

    GameManager<char> fourInRowGameManager(board,players);

    fourInRowGameManager.run();

    delete board;

    for (auto & player : players){
        delete player;
    }
}

#endif