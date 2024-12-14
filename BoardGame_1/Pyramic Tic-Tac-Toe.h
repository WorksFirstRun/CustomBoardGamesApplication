#ifndef CUSTOMBOARDGAMESAPPLICATION_PYRAMIC_TIC_TAC_TOE_H
#define CUSTOMBOARDGAMESAPPLICATION_PYRAMIC_TIC_TAC_TOE_H
#include <iomanip>
#include "../AssignmentDemo_WithBouns/BoardGame_Classes.h"

template<typename T>
class Pyramid_grid:public Board<T>{
private:
    int colum_size[3]={1,3,5};
public:
    Pyramid_grid ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    ~Pyramid_grid();
    T** GetBoard();
};

template<typename T>
class Pyramid_player:public Player<T>{
public:
    Pyramid_player(string  name,T symbol);
    void getmove(int& x, int& y) ;
};

template <typename T>
class Pyramid_Random_Player : public RandomPlayer<T>{
private:
    int colum_size[3]={1,3,5};
public:
    Pyramid_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};

template<typename T>
Pyramid_grid<T>::Pyramid_grid() {
    this->rows=3;
    this->board=new char*[this->rows];
    for(int i=0;i<this->rows;i++){
        this->board[i] = new char[colum_size[i]];
        for(int j=0;j<colum_size[i];j++){
            this->board[i][j]='0';
        }
    }
    this->n_moves=0;
}

template<typename T>
bool Pyramid_grid<T>::update_board(int x, int y, T symbol) {
    if (x < 0 || x >= this->rows || y < 0 || y >= colum_size[x]) {
        return false;
    }
    if (this->board[x][y] == '0') {
        this->board[x][y] = toupper(symbol);
        this->n_moves++;
        return true;
    }
    return false;
}

template <typename T>
void Pyramid_grid<T>::display_board() {
    for (int i = 0; i < 3; i++) {
        cout << setw(-6 * i + 24) << " ";
        for (int j = 0; j < colum_size[i]; j++) {
            cout << this->board[i][j] << "(" << i << "," << j << ")";
            if (j != colum_size[i] - 1) {
                cout << "|";
            }
        }
        cout << endl;
    }
}

template <typename T>
bool Pyramid_grid<T>::is_win() {
    if(this->board[0][0]==this->board[1][1]&&this->board[1][1]==this->board[2][2]&&this->board[0][0]!='0'){
        return true;
    }
    if(((this->board[0][0]==this->board[1][0]&&this->board[1][0]==this->board[2][0])&&this->board[1][0]!='0')||((this->board[0][0]==this->board[1][2]&&this->board[1][2]==this->board[2][4]))&&this->board[2][4]!='0') return true;
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j <= colum_size[i] - 3; j++) {
            if (this->board[i][j] != '0' &&
                this->board[i][j] == this->board[i][j + 1] &&
                this->board[i][j] == this->board[i][j + 2]) {
                return true;
            }
        }
    }
    return false;
}

template <typename T>
bool Pyramid_grid<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Pyramid_grid<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
T** Pyramid_grid<T>::GetBoard() {
    return this->board;
}

template <typename T>
Pyramid_player<T>::Pyramid_player(string name, T symbol)  : Player<T>(name, symbol) {};

template <typename T>
void Pyramid_player<T>::getmove(int& x, int& y) {
    cout <<this->name<< " Please enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

template <typename T>
Pyramid_Random_Player<T>::Pyramid_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void Pyramid_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->colum_size[x];
}

template <typename T>
Pyramid_grid<T>::~Pyramid_grid() {
    for (int i = 0; i < this->rows; i++) {
        delete[] this->board[i];
    }
    delete[] this->board;
}

class BoardGame1_Wrapper {
private:
    Pyramid_grid<char>* board;
    Player<char>* players[2];
    bool isInitialized();

public:
    enum PlayerType {
        Human,
        Random
    };
    PlayerType playersType[2];

    BoardGame1_Wrapper() : board(nullptr) {
        players[0] = nullptr;
        players[1] = nullptr;
    }

    void InitializeGame(string player1, string player2, PlayerType player1Type, PlayerType player2Type) {
        ClearGameState();
        
        board = new Pyramid_grid<char>();
        
        switch(player1Type) {
            case Human:
                players[0] = new Pyramid_player<char>(player1, 'X');
                break;
            case Random:
                players[0] = new Pyramid_Random_Player<char>('X');
                break;
        }
        players[0]->setBoard(board);
        
        switch(player2Type) {
            case Human:
                players[1] = new Pyramid_player<char>(player2, 'O');
                break;
            case Random:
                players[1] = new Pyramid_Random_Player<char>('O');
                break;
        }
        players[1]->setBoard(board);
        
        playersType[0] = player1Type;
        playersType[1] = player2Type;
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

    char** GetBoard() {
        if (!isInitialized()) {
            throw std::runtime_error("Game is not Initialized");
        }
        return board->GetBoard();
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



    ~BoardGame1_Wrapper() {
        ClearGameState();
    }
};

#endif