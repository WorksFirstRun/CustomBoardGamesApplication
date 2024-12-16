#ifndef EDITED_3X3_XO_H
#define EDITED_3X3_XO_H

#include "BoardGame_Classes.h"

template <typename T>
class X_O_Board:public Board<T> {
protected:
    int position=0;
public:
    X_O_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    void set_position(int x);
    bool Is_valid(int &x,int &y,T symbol);
    T get_symbol(int x, int y) const;


};


//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;


// Constructor for X_O_Board
template <typename T>
X_O_Board<T>::X_O_Board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = ' ';
        }
    }
    this->n_moves = 0;
}
template <typename T>
void X_O_Board<T>::set_position(int x) {
    this->position=x;
}
template <typename T>
bool X_O_Board<T>::Is_valid(int &x, int &y, T symbol) {
    return (x >= 0 && x < 3 && y >= 0 && y < 3 &&
            this->board[x][y] == ' ')&&position>=0 &&position<9&&(symbol=='X'||symbol=='O');
}


template <typename T>
bool X_O_Board<T>::update_board(int x, int y, T mark) {
    if (!Is_valid(x,y,mark)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }


    }
    else {
        this->n_moves++;
        this->board[x][y] = toupper(mark);
        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void X_O_Board<T>::display_board() {
    for (int i = 3*(position/3); i < (3*(position/3)+3); i++) {

        cout << "\n| ";
        for (int j = 3*(position%3); j < 3*(position%3)+3; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i%3][j%3] << " |";
        }
        cout << "\n-----------------------------";
    }
}

// Returns true if there is any winner
template <typename T>
bool X_O_Board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != ' ') ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != ' ')) {
            return true;
        }
    }

    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != ' ') ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != ' ')) {
        return true;
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool X_O_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool X_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

template <typename T>
T X_O_Board<T>::get_symbol(int x, int y) const {
    if (x >= 0 && x < 3 && y >= 0 && y < 3) {
        return this->board[x][y];
    }
    return ' ';
}




#endif //EDITED_3X3_XO_H
