
#ifndef CUSTOMBOARDGAMESAPPLICATION_ULTIMATE_TIC_TAC_TOE_H
#define CUSTOMBOARDGAMESAPPLICATION_ULTIMATE_TIC_TAC_TOE_H
#include "Edited_3x3_XO.h"
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
class Ultimate_grid{
private:
    int n_moves=0;
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
    return (x>=0 && x<9 && y>=0 && y<9&& (symbol=='X'||symbol=='O') &&Win[subGrid]!=' ');
}

template <typename T>
bool Ultimate_grid<T>::update_board(int x, int y, T symbol) {
    if (Is_valid(x, y, symbol)) {
        int subGrid = (x / 3) * 3 + (y / 3);
        int localx = x % 3;
        int localy = y % 3;
        if (Big_board[subGrid]->Is_valid(localx, localy, symbol)) {
            Big_board[subGrid]->update_board(localx, localy, symbol);
            if (Big_board[subGrid]->is_win() && Win[subGrid] == ' ') {
                Set_win(subGrid, symbol);
            }
            if (Big_board[subGrid]->is_draw() && Win[subGrid] == ' ') {
                Set_win(subGrid, 'D');
            }

            this->n_moves++;
            return true;
        }
    }
    return false;
}

template <typename T>
void Ultimate_grid<T>::display_board() {
    for(int i=0;i<3;i++){
        Big_board[i]->display_board();
    }
    for(int i=3;i<6;i++){
        Big_board[i]->display_board();
    }
    for(int i=6;i<9;i++){
        Big_board[i]->display_board();
    }
    cout.flush();
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

    return (this->n_moves == 27 && !is_win());
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



void RunBoardGame(){ // if you want to play the game in terminal
    Player<char>* players[2];
    Ultimate_grid<char> Grid;

    string playerXName, playerOName;
    cout << "Enter Player X name: ";
    cin >> playerXName;
    players[0] = new Ultimate_Player<char>(playerXName, 'X');

    cout << "Enter Player O name: ";
    cin >> playerOName;
    players[1] = new Ultimate_Player<char>(playerOName, 'O');

    Grid.display_board();
    int counter=0;
    int x, y;
    while (!Grid.game_is_over()) {
        for (int i : {0, 1}) {
            players[i]->getmove(x, y);
            counter++;
            while (!Grid.update_board(x, y, players[i]->getsymbol())) {
                cout << "Invalid move. Try again.\n";
                players[i]->getmove(x, y);
            }
            Grid.display_board();


            if (Grid.is_win()) {
                cout << players[i]->getname() << " wins!\n";
                 break;
            }

            if (Grid.is_draw()) {
                cout << "It's a draw!\n";
                break;
            }
        }
    }

    delete players[0];
    delete players[1];
}

#endif