
#ifndef CUSTOMBOARDGAMESAPPLICATION_FOUR_IN_A_ROW_H
#define CUSTOMBOARDGAMESAPPLICATION_FOUR_IN_A_ROW_H

#include "../AssignmentDemo_WithBouns/BoardGame_Classes.h"
#include "MinMax_FourInRow.h"

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

    T ** GetBoard();

    int GetMovesPlayedNumber();

    int * GetCurrentRowOfEachColumn();

};

template<typename T>
int *Four_in_a_Row_Board<T>::GetCurrentRowOfEachColumn() {
    return currentColumnX;
}


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



class BoardGame2_Wrapper{
private:
    Four_in_a_Row_Board<char> * board;
    Player<char> * players[2];
    bool isInitialized();
public:
    enum PlayerType{
        Human,
        Randomizer,
        AI};

    PlayerType playersType[2];

    void InitializeGame(string player1,string player2,PlayerType player1Type,PlayerType player2Type);
    char ** GetBoard();
    int GetMovesPlayed();
    int * GetCurrentRowOfEachColumn();
    string GetPlayer1Name();
    string GetPlayer2Name();

    void GetPlayer1Move(int &x, int &y);
    void GetPlayer2Move(int &x, int &y);

    void Player1PerformMove(int x,int y);
    void Player2PerformMove(int x, int y);

    bool isWin();
    bool isDraw();
    bool isGameOver();

    void ClearGameState();

    ~BoardGame2_Wrapper();


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
            this->currentColumnX[y]++;
            this->n_moves--;
            this->board[currentColumnX[y]][y] = 0;
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
    bool isValid1 = !(currentColumnX[y] < -1 || currentColumnX[y] > 6 || y < 0 || y > 6);
    bool isValid2 = false;
    if (isValid1){
        int currentRow = currentColumnX[y];
        if (currentRow == -1){
            currentRow = 0;
        }
        isValid2 = (symbol == 0 || this->board[currentRow][y] == 0 );
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

template<typename T>
T **Four_in_a_Row_Board<T>::GetBoard() {
    return this->board;
}

template<typename T>
int Four_in_a_Row_Board<T>::GetMovesPlayedNumber() {
    return this->n_moves;
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
    y = rand() % this->dimension;
}


/// --------------------------------------|
/// --> End of RandomPlayer Implementation|
/// --------------------------------------|


/*
void RunBoardGame(){ // if you want to play the game in terminal
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
        case 3:
            players[0] = new FourInRowMinMax<char>('X','O');
            players[0]->setBoard(board);
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
        case 3:
            players[1] = new FourInRowMinMax<char>('O','X');
            players[1]->setBoard(board);
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
}*/

/// Wrapper class to use in GUI
/// Implementation of it below


void BoardGame2_Wrapper::InitializeGame(std::string player1, std::string player2,
                                           BoardGame2_Wrapper::PlayerType player1Type,
                                           BoardGame2_Wrapper::PlayerType player2Type) {
    board = new Four_in_a_Row_Board<char>();
    playersType[0] = player1Type;
    playersType[1] = player2Type;

    switch(player1Type){
        case Human:
            players[0] = new Four_in_a_Row_Player<char>(player1,'X');
            break;
        case Randomizer:
            players[0] = new Four_in_a_Row_RandomPlayer<char>('X');
            break;
        case AI:
            players[0] = new FourInRowMinMax<char>('X','O');
            players[0]->setBoard(board);
            break;
        default:
            throw std::runtime_error("wrong playerType passed, consider looking at line 377 in function InitializeGame to debug if you want");
    }

    switch(player2Type){
        case Human:
            players[1] = new Four_in_a_Row_Player<char>(player2,'O');
            break;
        case Randomizer:
            players[1] = new Four_in_a_Row_RandomPlayer<char>('O');
            break;
        case AI:
            players[1] = new FourInRowMinMax<char>('O','X');
            players[1]->setBoard(board);
            break;
        default:
            throw std::runtime_error("wrong playerType passed, consider looking at line 393 in function InitializeGame to debug if you want");
    }

}

char **BoardGame2_Wrapper::GetBoard() {
    if (!isInitialized()){
        throw std::runtime_error("Game is not Initialized, Initialize first");
    }
    return board->GetBoard(); // i asked the dr for making some Modifications inside the board class to be able to return this , will change it when he approve it
}

int BoardGame2_Wrapper::GetMovesPlayed() {
    if (!isInitialized()){
        throw std::runtime_error("Game is not Initialized, Initialize first");
    }
    return board->GetMovesPlayedNumber(); // should be Changed when the doctor answer
}

int *BoardGame2_Wrapper::GetCurrentRowOfEachColumn() {
    if (!isInitialized()){
        throw std::runtime_error("Game is not Initialized, Initialize first");
    }
    return board->GetCurrentRowOfEachColumn();
}

string BoardGame2_Wrapper::GetPlayer1Name() {
    if (!isInitialized()){
        throw std::runtime_error("Game is not Initialized, Initialize first");
    }
    return players[0]->getname();
}

string BoardGame2_Wrapper::GetPlayer2Name() {
    if (!isInitialized()){
        throw std::runtime_error("Game is not Initialized, Initialize first");
    }
    return players[1]->getname();
}

void BoardGame2_Wrapper::GetPlayer1Move(int &x, int &y) {
    if (!isInitialized()){
        throw std::runtime_error("Game is not Initialized, Initialize first");
    }
    if (playersType[0] == Human){
        // do nothing, since you would enter the move Inside UI
        return;
    }

    players[0]->getmove(x,y);
}

void BoardGame2_Wrapper::GetPlayer2Move(int &x, int &y) {
    if (!isInitialized()){
        throw std::runtime_error("Game is not Initialized, Initialize first");
    }
    if (playersType[1] == Human){
        // do nothing, since you would enter the move Inside UI
        return;
    }

    players[1]->getmove(x,y);
}

void BoardGame2_Wrapper::Player1PerformMove(int x, int y) {
    if (!isInitialized()){
        throw std::runtime_error("Game is not Initialized, Initialize first");
    }
    if (!board->update_board(x,y,players[0]->getsymbol())){
         throw runtime_error("Move didn't performed since it's a bad move, line 470 in Player1PerformMove");
    }
}


void BoardGame2_Wrapper::Player2PerformMove(int x, int y) {
    if (!isInitialized()){
        throw std::runtime_error("Game is not Initialized, Initialize first");
    }
    if (!board->update_board(x,y,players[1]->getsymbol())){
        throw runtime_error("Move didn't performed since it's a bad move, line 477 in Player2PerformMove");
    }
}

bool BoardGame2_Wrapper::isWin() {
    if (!isInitialized()){
        throw std::runtime_error("Game is not Initialized, Initialize first");
    }
    return board->is_win();
}

bool BoardGame2_Wrapper::isDraw() {
    if (!isInitialized()){
        throw std::runtime_error("Game is not Initialized, Initialize first");
    }
    return board->is_draw();
}

bool BoardGame2_Wrapper::isGameOver() {
    if (!isInitialized()){
        throw std::runtime_error("Game is not Initialized, Initialize first");
    }
    return board->game_is_over();
}

void BoardGame2_Wrapper::ClearGameState() {
    if (isInitialized()){
        delete board;
        board = nullptr; // Now safe to check if the board is initialized

        delete players[0];
        players[0] = nullptr;

        delete players[1];
        players[1] = nullptr;
    }
}

bool BoardGame2_Wrapper::isInitialized() {
    return board != nullptr || players[0] != nullptr || players[1] != nullptr;
}

BoardGame2_Wrapper::~BoardGame2_Wrapper(){
    ClearGameState();
}




#endif
