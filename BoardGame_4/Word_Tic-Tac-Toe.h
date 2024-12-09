
#ifndef CUSTOMBOARDGAMESAPPLICATION_WORD_TIC_TAC_TOE_H
#define CUSTOMBOARDGAMESAPPLICATION_WORD_TIC_TAC_TOE_H

#include <iomanip>
#include "../AssignmentDemo_WithBouns/BoardGame_Classes.h"
#include <fstream>
#include <type_traits>
template<typename T>
class Word_grid:public Board<T>{
private:
    string filename;

public:
    Word_grid ();
    void set_filename();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    bool Is_valid(int &x,int &y,T symbol);
    ~Word_grid();

};
template<typename T>
class Word_player:public Player<T>{
public:
    Word_player(string  name,T symbol);
    void getmove(int& x, int& y) ;
};
template <typename T>
class Word_Random_Player : public RandomPlayer<T>{
public:
    Word_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};
template<typename T>
void Word_grid<T>::set_filename() {
    string name;
    cout<<"Enter the file name "<<endl;
    cin>>name;
    filename=name;
    ifstream file(filename);
    while(true) {
        if (!file.is_open()) {
            cout << "Error: Could not open file " << filename << endl;
            cin>>name;
            file.open(name);
            filename=name;
        } else break;
    }
}
template<typename T>

Word_grid<T>::Word_grid() {

    set_filename();
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
template<typename T>

bool Word_grid<T>::Is_valid(int &x, int &y, T symbol) {
    return (x >= 0 && x < 3 && y >= 0 && y < 3 &&
            toupper(symbol) >= 'A' && toupper(symbol) <= 'Z' &&
            this->board[x][y] == ' ');
}
template<typename T>

bool Word_grid<T>::update_board(int x, int y, T symbol) {
    if(this->Is_valid(x,y,symbol)){
        this->n_moves++;
        this->board[x][y] = toupper(symbol);
        return true;
    }
    return false;
}
template <typename T>
void Word_grid<T>::display_board() {
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
template <typename T>
bool Word_grid<T>::is_win() {
    ifstream file(filename);

    for (int i = 0; i < this->rows; i++) {
        string word1, word2;
        word1 = string(1, toupper(this->board[i][0])) + static_cast<char>(toupper(this->board[i][1])) +static_cast<char>( toupper(this->board[i][2]));
        word2 = string(1, toupper(this->board[0][i])) + static_cast<char>(toupper(this->board[1][i])) + static_cast<char>(toupper(this->board[2][i]));
        string currentWord;

        file.clear();
        file.seekg(0);
        while (file >> currentWord) {
            if (currentWord == word1 || currentWord == word2)
                return true;
        }
    }

    string word1, word2, currentWord;
    word1 = string(1, toupper(this->board[0][0])) + static_cast<char>(toupper(this->board[1][1])) + static_cast<char>(toupper(this->board[2][2]));
    word2 = string(1, toupper(this->board[0][2])) + static_cast<char>(toupper(this->board[1][1])) + static_cast<char>(toupper(this->board[2][0]));

    file.clear();
    file.seekg(0);
    while (file >> currentWord) {
        if (currentWord == word1 || currentWord == word2)
            return true;
    }
    return false;
}

template <typename T>
bool Word_grid<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}
template <typename T>

bool Word_grid<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
Word_player<T>::Word_player(std::string name, T symbol) :Player<T>(name,symbol){}

template <typename T>
void Word_player<T>::getmove(int& x, int& y) {
    cout << this->name<<" Please enter your move x and y (0 to 2) then enter the character separated by spaces : ";
    char input;
    cin >> x >> y>>input;

    this->symbol=input;

}

template <typename T>
Word_Random_Player<T>::Word_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}
template <typename T>
void Word_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
    this->symbol = 'A' + (rand() % 26);
}
template <typename T>
Word_grid<T>::~Word_grid() {
    for (int i = 0; i < this->rows; ++i) {
        delete[] this->board[i];
    }
    delete[] this->board;
}


void RunBoardGame(){ // if you want to play the game in terminal
    int choice;

    Board<char> * board = new Word_grid<char>();
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
            players[0] = new Word_player<char>(player1,'X');
            break;
        case 2:
            players[0] = new Word_Random_Player<char>('X');
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
            players[1] = new Word_player<char>(player2,'O');
            break;
        case 2:
            players[1] = new Word_Random_Player<char>('O');
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