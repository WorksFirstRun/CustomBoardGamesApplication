#ifndef _5X5X_O_H
#define _5X5X_O_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>

// Forward declarations
template <typename T> class 5x5_Board;
template <typename T> class 5x5_HumanPlayer;
template <typename T> class 5x5_RandomPlayer;
template <typename T> class 5x5_MinMaxPlayer;

//================= Board Class =================
template <typename T>
class 5x5_Board : public Board<T> {
private:
    int countThreeInARow(T symbol); 
    bool isValidMove(int x, int y, T symbol);

public:
    // Constructor
    5x5_Board() {
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
        return this->n_moves == 24;  // Game ends when 24 moves are made
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
class 5x5_HumanPlayer : public Player<T> {
private:
    static int player_count;  // Keep track of which player is being created (1 or 2)
    int player_number;        // Store whether this is player 1 or 2

public:
    5x5_HumanPlayer() : Player<T>("", ' ') {
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
            symbol = toupper(symbol);  // Convert to uppercase
        } while (symbol != 'X' && symbol != 'O');

        // If player 2 chooses the same symbol as player 1, give them the other symbol
        if (player_number == 2 && symbol == this->other_symbol) {
            cout << "Symbol already taken. You will be assigned: " 
                 << (symbol == 'X' ? 'O' : 'X') << endl;
            symbol = (symbol == 'X' ? 'O' : 'X');
        }
        
        this->name = name;
        this->symbol = symbol;
        
        if (player_number == 1) {
            this->other_symbol = symbol;  // Store first player's symbol
        }
    }

    void getmove(int& x, int& y) override {
        cout << "\nPlayer " << this->name << "'s turn (" << this->symbol << ")" << endl;
        cout << "Please enter your move x and y (0 to 4) separated by spaces: ";
        
        while (true) {
            cin >> x >> y;
            if (cin.fail() || x < 0 || x >= 5 || y < 0 || y >= 5) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter numbers between 0 and 4: ";
                continue;
            }
            break;
        }
    }

    static void resetPlayerCount() {
        player_count = 0;
    }

private:
    static T other_symbol;  // Store the first player's symbol to prevent duplicates
};

// Initialize static members
template <typename T>
int 5x5_HumanPlayer<T>::player_count = 0;

template <typename T>
T 5x5_HumanPlayer<T>::other_symbol = ' ';

//================= Random Player Class =================
template <typename T>
class 5x5_RandomPlayer : public Player<T> {
private:
    int dimension;

public:
    5x5_RandomPlayer(T symbol) : Player<T>("Random Computer Player", symbol) {
        dimension = 5;
        srand(static_cast<unsigned int>(time(0)));
    }

    void getmove(int& x, int& y) override {
        x = rand() % dimension;
        y = rand() % dimension;
        // Keep generating random moves until a valid one is found
        while (!this->boardPtr->update_board(x, y, this->symbol)) {
            x = rand() % dimension;
            y = rand() % dimension;
        }
        this->boardPtr->update_board(x, y, '.');  // Undo the move
    }
};

//================= MinMax Player Class =================
template <typename T>
class 5x5_MinMaxPlayer : public Player<T> {
private:
    int calculateMinMax(T symbol, bool isMaximizing) {
        // TODO: Implement MinMax algorithm
        // Consider three-in-a-row counts for evaluation
    }

    std::pair<int, int> getBestMove() {
        // TODO: Implement best move selection
        // Use calculateMinMax to evaluate positions
    }

public:
    5x5_MinMaxPlayer(T symbol) : Player<T>("AI Player", symbol) {}

    void getmove(int& x, int& y) override {
        // TODO: Implement AI move selection
        std::pair<int, int> move = getBestMove();
        x = move.first;
        y = move.second;
    }
};

//================= Helper Function Implementations =================
template <typename T>
int 5x5_Board<T>::countThreeInARow(T symbol) {
    int count = 0;
    
    // Check horizontal three-in-a-row
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j <= this->columns - 3; j++) {
            if (this->board[i][j] == symbol && 
                this->board[i][j+1] == symbol && 
                this->board[i][j+2] == symbol) {
                count++;
            }
        }
    }
    
    // Check vertical three-in-a-row
    for (int i = 0; i <= this->rows - 3; i++) {
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] == symbol && 
                this->board[i+1][j] == symbol && 
                this->board[i+2][j] == symbol) {
                count++;
            }
        }
    }
    
    // Check diagonal (top-left to bottom-right)
    for (int i = 0; i <= this->rows - 3; i++) {
        for (int j = 0; j <= this->columns - 3; j++) {
            if (this->board[i][j] == symbol && 
                this->board[i+1][j+1] == symbol && 
                this->board[i+2][j+2] == symbol) {
                count++;
            }
        }
    }
    
    // Check diagonal (top-right to bottom-left)
    for (int i = 0; i <= this->rows - 3; i++) {
        for (int j = this->columns - 1; j >= 2; j--) {
            if (this->board[i][j] == symbol && 
                this->board[i+1][j-1] == symbol && 
                this->board[i+2][j-2] == symbol) {
                count++;
            }
        }
    }
    
    return count;
}

template <typename T>
bool 5x5_Board<T>::isValidMove(int x, int y, T symbol) {
    // Check if coordinates are within bounds
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns) {
        return false;
    }
    
    // For new moves: cell must be empty
    if (symbol != '.') {
        return this->board[x][y] == '.';
    }
    
    // For undo: cell must contain a symbol
    return this->board[x][y] != '.';
}

#endif //_5X5X_O_H
