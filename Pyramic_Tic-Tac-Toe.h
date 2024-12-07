#ifndef CUSTOMBOARDGAMESAPPLICATION_PYRAMIC_TIC_TAC_TOE_H
#define CUSTOMBOARDGAMESAPPLICATION_PYRAMIC_TIC_TAC_TOE_H
#include <iomanip>
#include "BoardGame_Classes.h"

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

//    colum
    if(this->board[0][0]==this->board[1][1]&&this->board[1][1]==this->board[2][2]&&this->board[0][0]!='0'){
        char test1=this->board[0][0];
        char test2=this->board[1][1];

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
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
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

#endif
