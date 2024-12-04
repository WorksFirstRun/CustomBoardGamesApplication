#ifndef _5X5X_O_H
#define _5X5X_O_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>

template <typename T> class FiveByFive_Board;
template <typename T> class FiveByFive_HumanPlayer;
template <typename T> class FiveByFive_RandomPlayer;
template <typename T> class 5x5_MinMaxPlayer;

//================= Board Class =================
template <typename T>
class FiveByFive_Board : public Board<T> {
private:
    int countThreeInARow(T symbol); 
    bool isValidMove(int x, int y, T symbol);

public:
    FiveByFive_Board() {
        this->rows = this->columns = 5;
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
        for (int i = 0; i < this->rows; i++) {
            cout << "\n| ";
            for (int j = 0; j < this->columns; j++) {
                cout << "(" << i << "," << j << ")";
                cout << setw(2) << this->board[i][j] << " |";
            }
            cout << "\n-----------------------------";
        }
        cout << endl;
    }

    bool is_win() override {
        int count_X = countThreeInARow('X');
        int count_O = countThreeInARow('O');
        if (this->n_moves == 24) {
            return count_X != count_O;
        }
        return false;
    }

    bool is_draw() override {
        if (this->n_moves == 24) {
            int count_X = countThreeInARow('X');
            int count_O = countThreeInARow('O');
            return count_X == count_O;
        }
        return false;
    }

    bool game_is_over() override {
        return this->n_moves == 24;  
    }

    
    T** GetBoardState() {
        return this->board;
    }

    int getMovesPlayed() {
        return this->n_moves;
    }
};

//================= Human Player Class =================
template <typename T>
class FiveByFive_HumanPlayer : public Player<T> {
private:
    static int player_count;  
    int player_number;        

public:
    FiveByFive_HumanPlayer() : Player<T>("", ' ') {
        player_count++;
        if (player_count > 2) {
            throw runtime_error("Cannot create more than 2 players");
        }
        
        player_number = player_count;
        initializePlayer();
    }

    void initializePlayer() {
        string name;
        T symbol;
        
        cout << "\nPlayer " << player_number << " setup:" << endl;
        cout << "Enter your name: ";
        cin >> name;
        
        do {
            cout << "Choose your symbol (X or O): ";
            cin >> symbol;
            symbol = toupper(symbol);  
        } 
        
        while (symbol != 'X' && symbol != 'O');

        // If player 2 chooses the same symbol as player 1  give them the other symbol
        if (player_number == 2 && symbol == this->other_symbol) {
            cout << "Symbol already taken. You will be assigned: " 

                 << (symbol == 'X' ? 'O' : 'X') << endl;
            symbol = (symbol == 'X' ? 'O' : 'X');
        }
        
        this->name = name;
        this->symbol = symbol;
        
        if (player_number == 1) {
            this->other_symbol = symbol;  
        }
    }

    void getmove(int& x, int& y) override {
        cout << "\nPlayer " << this->name << "'s turn (" << this->symbol << ")" << endl;
        cout << "Please enter your move x and y (0 to 4) separated by spaces: ";
                this->boardPtr->display_board();
            cin >> x >> y;
            
    }

    static void resetPlayerCount() {
        player_count = 0;
    }

private:
    static T other_symbol; 
};

template <typename T>
int FiveByFive_HumanPlayer<T>::player_count = 0;

template <typename T>
T FiveByFive_HumanPlayer<T>::other_symbol = ' ';

//================= Random Player Class =================
template <typename T>
class FiveByFive_RandomPlayer : public Player<T> {
private:
    int dimension;

public:
    FiveByFive_RandomPlayer(T symbol) : Player<T>("Random Computer Player", symbol) {
        dimension = 5;
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
int FiveByFive_Board<T>::countThreeInARow(T symbol) {
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
bool FiveByFive_Board<T>::isValidMove(int x, int y, T symbol) {
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns) {
        return false;
    }
    
    if (symbol != '.') {
        return this->board[x][y] == '.';
    }
    
    return this->board[x][y] != '.';
}

#endif 
