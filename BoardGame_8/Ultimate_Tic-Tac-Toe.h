#ifndef CUSTOMBOARDGAMESAPPLICATION_ULTIMATE_TIC_TAC_TOE_H
#define CUSTOMBOARDGAMESAPPLICATION_ULTIMATE_TIC_TAC_TOE_H
#include "Edited_3x3_XO.h."
#include <map>

template <typename T>
class Ultimate_Player : public Player<T> {
public:
    Ultimate_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};
template <typename T>
class Ultimate_Random_Player : public RandomPlayer<T>{
public:
    Ultimate_Random_Player(T symbol);
    void getmove(int &x, int &y) ;
};

template <typename T>
class Ultimate_grid:public Board<T>{
private:
    int n_moves=0;
    int current_board = -1;  // -1 means any board can be played
public:
    X_O_Board<T>*Big_board[9];
    map<int,char>Win;
public:
    Ultimate_grid ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    bool Is_valid(int &x,int &y,T symbol);
    void Set_win(int position,T symbol);
    ~Ultimate_grid() ;
    T** GetBoard() {
        return this->board;
    }
    int get_current_board() {
    
        return current_board;
    }
    bool is_sub_board_complete(int boardIndex) {

        if (boardIndex < 0 || boardIndex >= 9) return false;
        return Win[boardIndex] != ' ';
    }
};
template <typename T>
void Ultimate_grid<T>::Set_win(int position,T symbol) {
    Win[position]=symbol;
}
template <typename T>
Ultimate_grid<T>::Ultimate_grid() {
    for(int i=0;i<9;i++){
        Big_board[i] = new X_O_Board<T>();
        Big_board[i]->set_position(i);
        Win[i]=' ';
    }
    this->n_moves = 0;

}
template <typename T>

bool Ultimate_grid<T>::Is_valid(int &x, int &y, T symbol) {
    int subGrid = (x / 3) * 3 + (y / 3);
    return (x>=0 && x<9 && y>=0 && y<9&& (symbol=='X'||symbol=='O') &&Win[subGrid]==' ');
}

template <typename T>
bool Ultimate_grid<T>::update_board(int x, int y, T symbol) {
    if (Is_valid(x, y, symbol)) {
        int subGrid = (x / 3) * 3 + (y / 3);
        int localx = x % 3;
        int localy = y % 3;
        
        if (current_board != -1 && subGrid != current_board) {
            return false;
        }
        
        if (Big_board[subGrid]->Is_valid(localx, localy, symbol)) {
            Big_board[subGrid]->update_board(localx, localy, symbol);
            if (Big_board[subGrid]->is_win() && Win[subGrid] == ' ') {
                Set_win(subGrid, symbol);
            }
            if (Big_board[subGrid]->is_draw() && Win[subGrid] == ' ') {
                Set_win(subGrid, 'D');
            }
            
            
            current_board = (localx * 3 + localy);
            if (Win[current_board] != ' ') {
                current_board = -1;  
            }
            
            this->n_moves++;
            return true;
        }
    }
    return false;
}

template <typename T>
void Ultimate_grid<T>::display_board() {
    for(int i=0;i<9;i++){
        Big_board[i]->display_board();
    }
    cout << endl;
}
template <typename T>
bool Ultimate_grid<T>::is_win() {

    for (int i = 0; i < 3; i++) {
        if ((Win[i * 3] != ' ' && Win[i * 3] == Win[i * 3 + 1] && Win[i * 3 + 1] == Win[i * 3 + 2]) ||  // Rows
            (Win[i] != ' ' && Win[i] == Win[i + 3] && Win[i + 3] == Win[i + 6])) {                     // Columns
            return true;
        }
    }
    // Check diagonals
    if ((Win[0] != ' ' && Win[0] == Win[4] && Win[4] == Win[8]) ||
        (Win[2] != ' ' && Win[2] == Win[4] && Win[4] == Win[6])) {
        return true;
    }
    return false;
}
template <typename T>
bool Ultimate_grid<T>::is_draw() {

    return (this->n_moves == 81 && !is_win());
}

template <typename T>
bool Ultimate_grid<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
Ultimate_Player<T>::Ultimate_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Ultimate_Player<T>::getmove(int& x, int& y) {
    cout << this->name<<" Please enter your move x and y (0 to 2)  : ";
    cin >> x >> y;
}
template <typename T>
Ultimate_grid<T>::~Ultimate_grid() {
    for (int i = 0; i < 9; ++i) {
        delete Big_board[i];
        Big_board[i] = nullptr;
    }
}
template <typename T>
Ultimate_Random_Player<T>::Ultimate_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Ultimate_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % 10;
    y = rand() % 10;
}


class BoardGame8_Wrapper {
private:
    Ultimate_grid<char>* board;
    Player<char>* players[2];
    bool isInitialized();

public:
    enum PlayerType {
        Human,
        Random
    };
    PlayerType playersType[2];

    BoardGame8_Wrapper() : board(nullptr) {
        players[0] = nullptr;
        players[1] = nullptr;
    }

    void InitializeGame(string player1, string player2, PlayerType player1Type, PlayerType player2Type) {
        ClearGameState();
        board = new Ultimate_grid<char>();
        
        switch(player1Type) {
            case Human:
                players[0] = new Ultimate_Player<char>(player1, 'X');
                break;
            case Random:
                players[0] = new Ultimate_Random_Player<char>('X');
                break;
        }
        players[0]->setBoard(board);
        
        switch(player2Type) {
            case Human:
                players[1] = new Ultimate_Player<char>(player2, 'O');
                break;
            case Random:
                players[1] = new Ultimate_Random_Player<char>('O');
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

    int GetCurrentBoard() {
        if (!isInitialized()) {
            throw std::runtime_error("Game is not Initialized");
        }
        return board->get_current_board();
    }

    bool IsSubBoardComplete(int boardIndex) {
        if (!isInitialized()) {
            throw std::runtime_error("Game is not Initialized");
        }
        return board->is_sub_board_complete(boardIndex);
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

    ~BoardGame8_Wrapper() {
        ClearGameState();
    }

    int GetMovesPlayed() {
        if (!isInitialized()) {
            throw runtime_error("Game is Not initialized ");
        }
        return board->n_moves;
    }
};

#endif
