
#ifndef CUSTOMBOARDGAMESAPPLICATION_FOUR_IN_A_ROW_H
#define CUSTOMBOARDGAMESAPPLICATION_FOUR_IN_A_ROW_H

#include "../AssignmentDemo_WithBouns/BoardGame_Classes.h"

template <typename T>
class Four_in_a_Row_Board : public Board<T>{
private:
    int currentColumnX[7];
    bool isMoveValid(int x,int y,T symbol);
public:
    Four_in_a_Row_Board();

    bool update_board(int x, int y, T symbol) override;

    void display_board() override;

    bool is_win() override;

    bool is_draw() override;

    bool game_is_over() override;

};


template <typename T>
class Four_in_a_Row_Player : public Player<T>{
public:
    Four_in_a_Row_Player(string name,T symbol);

    void getmove(int& x, int& y) override;
};

template <typename T>
class Four_in_a_Row_RandomPlayer : public RandomPlayer<T>{
public:
    Four_in_a_Row_RandomPlayer(T symbol);

    void getmove(int& x, int& y) override;

};

///###############################################################################################
///#################################### Implementation Below #####################################
///###############################################################################################


/// ||| Board Implementation |||
/// vvv                      vvv

template<typename T>
Four_in_a_Row_Board<T>::Four_in_a_Row_Board() {
    this->rows = 6;
    this->columns = 7;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }

    for (int & i : currentColumnX){
        i = 5;
    }

    this->n_moves = 0;
}


template<typename T>
bool Four_in_a_Row_Board<T>::update_board(int x, int y, T symbol) {
    if (isMoveValid(x,y,symbol)) {
        if (symbol == 0){
            this->n_moves--;
            this->board[currentColumnX[y]][y] = 0;
            this->currentColumnX[y]++;
        }
        else {
            this->n_moves++;
            this->board[currentColumnX[y]][y] = toupper(symbol);
            this->currentColumnX[y]--;
        }

        return true;
    }
    return false;
}

template<typename T>
bool Four_in_a_Row_Board<T>::isMoveValid(int x, int y,T symbol) {
    bool isValid1 = !(currentColumnX[y] < 0 || currentColumnX[y] > 5 || y < 0 || y > 7);
    bool isValid2 = false;
    if (isValid1){
        isValid2 = (this->board[currentColumnX[y]][y] == 0|| symbol == 0);
    }
    return isValid1 && isValid2;
}

template<typename T>
void Four_in_a_Row_Board<T>::display_board() {
    int rows = this->rows;
    int cols = this->columns;

    cout << "  ";
    for (int col = 0; col < cols; ++col) {
        cout << "  " << col  << " ";
    }
    cout << endl;

    for (int row = 0; row < rows; ++row) {

        cout << "  ";
        for (int col = 0; col < cols; ++col) {
            cout << "+---";
        }
        cout << "+" << endl;


        cout << "  ";
        for (int col = 0; col < cols; ++col) {
            cout << "| " << this->board[row][col] << " ";
        }
        cout << "|" << endl;
    }


    cout << "  ";
    for (int col = 0; col < cols; ++col) {
        cout << "+---";
    }
    cout << "+" << endl;
}


template<typename T>
bool Four_in_a_Row_Board<T>::is_win() {
    // Check for horizontal wins
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j <= this->columns - 4; j++) {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i][j+1] &&
                this->board[i][j+1] == this->board[i][j+2] &&
                this->board[i][j+2] == this->board[i][j+3]) {
                return true;
            }
        }
    }

    // Check for vertical wins
    for (int i = 0; i <= this->rows - 4; i++) {
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i+1][j] &&
                this->board[i+1][j] == this->board[i+2][j] &&
                this->board[i+2][j] == this->board[i+3][j]) {
                return true;
            }
        }
    }

    // Check for top-left to bottom-right diagonals
    for (int i = 0; i <= this->rows - 4; i++) {
        for (int j = 0; j <= this->columns - 4; j++) {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i+1][j+1] &&
                this->board[i+1][j+1] == this->board[i+2][j+2] &&
                this->board[i+2][j+2] == this->board[i+3][j+3]) {
                return true;
            }
        }
    }

    // Check for bottom-left to top-right diagonals
    for (int i = this->rows - 1; i >= 3; i--) {
        for (int j = 0; j <= this->columns - 4; j++) {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i-1][j+1] &&
                this->board[i-1][j+1] == this->board[i-2][j+2] &&
                this->board[i-2][j+2] == this->board[i-3][j+3]) {
                return true;
            }
        }
    }

    return false;
}



template<typename T>
bool Four_in_a_Row_Board<T>::is_draw() {
    return (this->n_moves == 42 && !is_win());
}


template<typename T>
bool Four_in_a_Row_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

/// -------------------------------|
/// --> End of Board Implementation|
/// -------------------------------|



/// ||| Player Implementation |||
/// vvv                       vvv

template<typename T>
Four_in_a_Row_Player<T>::Four_in_a_Row_Player(std::string name, T symbol) : Player<T>(name,symbol){}

template<typename T>
void Four_in_a_Row_Player<T>::getmove(int &x, int &y) {
    cout << "\n Select the column you want to drop " << this->symbol << " in it: ";
    cin >> y;
}



/// --------------------------------|
/// --> End of Player Implementation|
/// --------------------------------|



/// ||| RandomPlayer Implementation |||
/// vvv                             vvv


template<typename T>
Four_in_a_Row_RandomPlayer<T>::Four_in_a_Row_RandomPlayer(T symbol) : RandomPlayer<T>(symbol){
    this->dimension = 7;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template<typename T>
void Four_in_a_Row_RandomPlayer<T>::getmove(int &x, int &y) {
    y = rand() & this->dimension;
}


/// --------------------------------------|
/// --> End of RandomPlayer Implementation|
/// --------------------------------------|


/// minmax algorithm below just in case



/// end of minmax




void RunBoardGame(){
    int choice;

    Board<char> * board = new Four_in_a_Row_Board<char>();
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
            players[0] = new Four_in_a_Row_Player<char>(player1,'X');
            break;
        case 2:
            players[0] = new Four_in_a_Row_RandomPlayer<char>('X');
            break;
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
            players[1] = new Four_in_a_Row_Player<char>(player2,'O');
            break;
        case 2:
            players[1] = new Four_in_a_Row_RandomPlayer<char>('O');
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
