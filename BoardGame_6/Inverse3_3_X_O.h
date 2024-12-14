#ifndef INVERSE3_3_X_O_H
#define INVERSE3_3_X_O_H

#include "../AssignmentDemo_WithBouns/BoardGame_Classes.h"
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

    char currentSymbol;
    char winnerSymbol;
    bool someOneWon;
public:
    ThreeByThree_Board() {
        someOneWon = false;
        currentSymbol = 'X';
        winnerSymbol = ' ';
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

    bool isThere_a_Winner(){
        return someOneWon;
    }

    // Core game functions
    bool update_board(int x, int y, T symbol) override {
        if (isValidMove(x,y,symbol)) {
            if (symbol == '.'){
                this->n_moves--;
                this->board[x][y] = '.';
                DecideWhoWins();
            }

            else if (someOneWon){
                currentSymbol = symbol;
                return true;
            }

            else {
                this->n_moves++;
                this->board[x][y] = symbol;
                currentSymbol = symbol;
            }
            DecideWhoWins();
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
        return winnerSymbol == currentSymbol;
    }

    bool is_draw() override {
        if (this->n_moves == 9) {
            int count_X = countThreeInARow('X');
            int count_O = countThreeInARow('O');
            return count_X == count_O;
        }
        return false;
    }
    void DecideWhoWins() {
        int count_X = countThreeInARow('X');
        int count_O = countThreeInARow('O');

        if (count_X > 0){
            winnerSymbol = 'O';
            someOneWon = true;
        }
        else if (count_O > 0){
            winnerSymbol = 'X';
            someOneWon = true;
        }
        else{
            someOneWon = false;
            winnerSymbol = ' ';
        }
    }
    bool game_is_over() override {
        return is_draw() || is_win();
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
        if (dynamic_cast<ThreeByThree_Board<char>*>(this->boardPtr)->isThere_a_Winner()){
            x = -1;
            y = -1;
            return;
        }
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
    ThreeByThree_RandomPlayer(T symbol) : Player<T>("Random Computer Player",symbol) {
        dimension = 3;
        srand(static_cast<unsigned int>(time(0)));
    }

    void getmove(int& x, int& y) override {
        if (dynamic_cast<ThreeByThree_Board<char>*>(this->boardPtr)->isThere_a_Winner()){
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
    if (x == -1 && y == -1 && someOneWon){
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


class BoardGame6_Wrapper {
private:
    Misere_grid<char>* board;
    Player<char>* players[2];
    bool isInitialized();

public:
    enum PlayerType {
        Human,
        Random
    };
    PlayerType playersType[2];

    BoardGame6_Wrapper() : board(nullptr) {
        players[0] = nullptr;
        players[1] = nullptr;
    }

    void InitializeGame(string player1, string player2, PlayerType player1Type, PlayerType player2Type) {
        ClearGameState();
        board = new Misere_grid<char>();
        
        switch(player1Type) {
            case Human:
                players[0] = new Misere_Player<char>(player1, 'X');
                break;
            case Random:
                players[0] = new Misere_Random_Player<char>('X');
                break;
        }
        players[0]->setBoard(board);
        
        switch(player2Type) {
            case Human:
                players[1] = new Misere_Player<char>(player2, 'O');
                break;
            case Random:
                players[1] = new Misere_Random_Player<char>('O');
                break;
        }
        players[1]->setBoard(board);
        
        playersType[0] = player1Type;
        playersType[1] = player2Type;
    }

    char** GetBoard() {
        if (!isInitialized()) {
            throw std::runtime_error("Game is not Initialized");
        }
        return board->GetBoard();
    }

    string GetPlayer1Name() {
        if (!isInitialized()) {
            throw std::runtime_error("Game is not Initialized");
        }
        return players[0]->getname();
    }

    string GetPlayer2Name() {
        if (!isInitialized()) {
            throw std::runtime_error("Game is not Initialized");
        }
        return players[1]->getname();
    }

    void GetPlayer1Move(int& x, int& y) {
        if (!isInitialized()) {
            throw std::runtime_error("Game is not Initialized");
        }
        if (playersType[0] == Human) {
            return;
        }
        players[0]->getmove(x, y);
    }

    void GetPlayer2Move(int& x, int& y) {
        if (!isInitialized()) {
            throw std::runtime_error("Game is not Initialized");
        }
        if (playersType[1] == Human) {
            return;
        }
        players[1]->getmove(x, y);
    }

    void Player1PerformMove(int x, int y) {
        if (!isInitialized()) {
            throw std::runtime_error("Game is not Initialized");
        }
        if (!board->update_board(x, y, players[0]->getsymbol())) {
            throw std::runtime_error("Invalid move for Player 1");
        }
    }

    void Player2PerformMove(int x, int y) {
        if (!isInitialized()) {
            throw std::runtime_error("Game is not Initialized");
        }
        if (!board->update_board(x, y, players[1]->getsymbol())) {
            throw std::runtime_error("Invalid move for Player 2");
        }
    }

    bool isWin() {
        if (!isInitialized()) {
            throw std::runtime_error("Game is not Initialized");
        }
        return board->is_win();
    }

    bool isDraw() {
        if (!isInitialized()) {
            throw std::runtime_error("Game is not Initialized");
        }
        return board->is_draw();
    }

    bool isGameOver() {
        if (!isInitialized()) {
            throw std::runtime_error("Game is not Initialized");
        }
        return board->game_is_over();
    }

    void ClearGameState() {
        if (isInitialized()) {
            delete board;
            board = nullptr;
            delete players[0];
            players[0] = nullptr;
            delete players[1];
            players[1] = nullptr;
        }
    }

    bool isInitialized() {
        return board != nullptr && players[0] != nullptr && players[1] != nullptr;
    }

    ~BoardGame6_Wrapper() {
        ClearGameState();
    }
};

#endif 