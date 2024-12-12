
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
class Ultimate_grid : public Board<T>{
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
    int choice;

    Board<char> * board = new Ultimate_grid<char>();
    Player<char> * players[2];

    string player1,player2;


    cout << "Four in Row GameBoard2 \n";

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
            players[0] = new Ultimate_Player<char>(player1,'X');
            break;
        case 2:
            players[0] = new Ultimate_Random_Player<char>('X');
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
            players[1] = new Ultimate_Player<char>(player2,'O');
            break;
        case 2:
            players[1] = new Ultimate_Random_Player<char>('O');
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