#ifndef _5X5X_O_H
#define _5X5X_O_H

#include "../AssignmentDemo_WithBouns/BoardGame_Classes.h"
#include <iostream>
#include <iomanip>

template <typename T> class FiveByFive_Board;
template <typename T> class FiveByFive_HumanPlayer;
template <typename T> class FiveByFive_RandomPlayer;

//================= Board Class =================
template <typename T>
class FiveByFive_Board : public Board<T> {
private:
    int countThreeInARow(T symbol);
    bool isValidMove(int x, int y, T symbol);
    bool playersTurnsFinished;
    bool playerTurn;
public:
    bool isPlayerTurnsFinished(){
        return playersTurnsFinished;
    }

    FiveByFive_Board() {
        playersTurnsFinished = false;
        playerTurn = false;
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
            playerTurn = !playerTurn;
            if (symbol == '.'){
                this->n_moves--;
                this->board[x][y] = '.';
                if (this->n_moves < 24){
                    playersTurnsFinished = false;
                }
            }

            else if (playersTurnsFinished){
                this->n_moves = max(this->n_moves,25);
                return true;
            }

            else {
                this->n_moves++;
                this->board[x][y] = symbol;
                if (this->n_moves == 24){
                    playersTurnsFinished = true;
                }
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
        if (this->n_moves == 25) {
            int count_X = countThreeInARow('X');
            int count_O = countThreeInARow('O');
            if (playerTurn){
                return count_X > count_O;
            }
            else if (!playerTurn){
                return count_X < count_O;
            }
        }
        return false;
    }

    bool is_draw() override {
        if (this->n_moves == 25) {
            int count_X = countThreeInARow('X');
            int count_O = countThreeInARow('O');
            return count_X == count_O;
        }
        return false;
    }

    string whoWon(const string& player1Name, const string& player2Name) {
        int count_X = countThreeInARow('X');
        int count_O = countThreeInARow('O');

        if (this->n_moves == 24) {

            if (count_X > count_O) {
                return player1Name;  
            } else if (count_O > count_X) {
                return player2Name;  
            }
        }
        return ""; 
    }

    bool game_is_over() override {
        return is_draw() || is_win();
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
public:

    FiveByFive_HumanPlayer(string n,T symbol) : Player<T>(n,symbol){}

    void getmove(int& x, int& y) override {
        if (dynamic_cast<FiveByFive_Board<char>*>(this->boardPtr)->isPlayerTurnsFinished()){
            x = -1;
            y = -1;
            return;
        }
        cout << "\nPlayer " << this->name << "'s turn (" << this->symbol << ")" << endl;
        cout << "Please enter your move x and y (0 to 4) separated by spaces: ";

        cin >> x >> y;

    }
};


//================= Random Player Class =================
template <typename T>
class FiveByFive_RandomPlayer : public Player<T> {
private:
    int dimension;

public:
    FiveByFive_RandomPlayer(T symbol) : Player<T>(symbol) {
        this->name = "Random Computer Player";
        dimension = 5;
        srand(static_cast<unsigned int>(time(0)));
    }

    void getmove(int& x, int& y) override {
        if (dynamic_cast<FiveByFive_Board<char>*>(this->boardPtr)->isPlayerTurnsFinished()){
            x = -1;
            y = -1;
            return;
        }
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
    if (x == -1 && y == -1){
        return true;
    }
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

    Board<char> * board = new FiveByFive_Board<char>();
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
            players[0] = new FiveByFive_HumanPlayer<char>(player1,'X');
            players[0]->setBoard(board);
            break;
        case 2:
            players[0] = new FiveByFive_RandomPlayer<char>('X');
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
            players[1] = new FiveByFive_HumanPlayer<char>(player2,'O');
            players[1]->setBoard(board);
            break;
        case 2:
            players[1] = new FiveByFive_RandomPlayer<char>('O');
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
