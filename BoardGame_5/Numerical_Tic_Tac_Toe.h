
#ifndef CUSTOMBOARDGAMESAPPLICATION_NUMERICAL_TIC_TAC_TOE_H
#define CUSTOMBOARDGAMESAPPLICATION_NUMERICAL_TIC_TAC_TOE_H

#include "../AssignmentDemo_WithBouns/BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "MinMax_NumericalTicTacToe.h"
using namespace std;

template<typename T>
class NumericalTTT_Board : public Board<T>{
private:
    bool isValidMove(int x, int y, T symbol);
public:
    NumericalTTT_Board();

    bool update_board(int x,int y, T symbol) override;

    void display_board() override;

    bool is_win() override;

    bool is_draw() override;

    bool game_is_over() override;

    T ** GetBoardNumbers();

    int GetMovesPlayed();
};

template<typename T>
class NumericalTTT_CommonPlayerFunctions : public Player<T>{
protected:
    list<int> * availableNumbers;

public:
    void RemoveUsedNumber(T number);
    NumericalTTT_CommonPlayerFunctions(string n, T symbol);
    list<int> * getAvailableNumbers();
    ~NumericalTTT_CommonPlayerFunctions();
};

template<typename T>
class NumericalTTT_Player : public NumericalTTT_CommonPlayerFunctions<T>{
private:
    bool isNumberAvailable(T number);
public:
    NumericalTTT_Player(string n, T symbol);

    void getmove(int &x,int &y) override;

};


template<typename T>
class NumericalTTT_RandomPlayer : public NumericalTTT_CommonPlayerFunctions<T>{
private:
    int dimension;
public:
    NumericalTTT_RandomPlayer(string n,T symbol);

    void getmove(int &x,int &y) override;

};


class BoardGame5_Wrapper{
private:
    NumericalTTT_Board<int> * board;
    Player<int> * players[2];
    bool isInitialized();
public:
    enum PlayerType{
        Human,
        Randomizer,
        AI};

    PlayerType playersType[2];

    void InitializeGame(string player1,string player2,PlayerType player1Type,PlayerType player2Type);
    int ** GetBoard();
    int GetMovesPlayed();
    vector<int> GetAvailableNumbersForPlayer1();
    vector<int> GetAvailableNumbersForPlayer2();
    string GetPlayer1Name();
    string GetPlayer2Name();

    void GetPlayer1Move(int &x, int &y,int & symbol);
    void GetPlayer2Move(int &x, int &y,int & symbol);

    void Player1PerformMove(int x,int y);
    void Player2PerformMove(int x, int y);

    bool isWin();
    bool isDraw();
    bool isGameOver();

    void ClearGameState();

    ~BoardGame5_Wrapper();


};


///###############################################################################################
///#################################### Implementation Below #####################################
///###############################################################################################



template<typename T>
NumericalTTT_Board<T>::NumericalTTT_Board() {
    this->rows = this->columns = 3;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template<typename T>
bool NumericalTTT_Board<T>::update_board(int x, int y, T symbol) {
    if (isValidMove(x,y,symbol)) {
        if (symbol == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = symbol;
        }

        return true;
    }
    return false;
}

template<typename T>
void NumericalTTT_Board<T>::display_board() {
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

template<typename T>
bool NumericalTTT_Board<T>::is_win() {
    for (int i = 0; i < this->rows; i++) {
       if ((this->board[i][0] + this->board[i][1] + this->board[i][2] == 15 &&
            this->board[i][0] && this->board[i][1] && this->board[i][2]) ||
               (this->board[0][i] + this->board[1][i] + this->board[2][i] == 15  &&
                   this->board[0][i] && this->board[1][i] && this->board[2][i]) ){
           return true;
       }
    }

    if (this->board[0][0] + this->board[1][1] + this->board[2][2] == 15 &&
            this->board[0][0] && this->board[1][1] && this->board[2][2]){
        return true;
    }

    if (this->board[2][0] + this->board[1][1] + this->board[0][2] == 15 &&
            this->board[2][0] && this->board[1][1] && this->board[0][2]){
        return true;
    }

    return false;
}

template<typename T>
bool NumericalTTT_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template<typename T>
bool NumericalTTT_Board<T>::game_is_over() {
    return is_win() || is_draw();
}


template<typename T>
bool NumericalTTT_Board<T>::isValidMove(int x, int y, T symbol) {
    return !(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| symbol == 0);
}

template<typename T>
T **NumericalTTT_Board<T>::GetBoardNumbers() {
    return this->board;
}



template<typename T>
int NumericalTTT_Board<T>::GetMovesPlayed() {
    return this->n_moves;
}

/// End of Board Implementation ----------------------|

template<typename T>
list<int> * NumericalTTT_CommonPlayerFunctions<T>::getAvailableNumbers() {
    return availableNumbers;
}


template<typename T>
void NumericalTTT_CommonPlayerFunctions<T>::RemoveUsedNumber(T number) {
    auto it = find(availableNumbers->begin(), availableNumbers->end(), number);
    if (it != availableNumbers->end()) {
        availableNumbers->erase(it);
    }
}

template<typename T>
NumericalTTT_CommonPlayerFunctions<T>::~NumericalTTT_CommonPlayerFunctions() {
    delete availableNumbers;
}

template<typename T>
NumericalTTT_CommonPlayerFunctions<T>::NumericalTTT_CommonPlayerFunctions(string n,T symbol) :
Player<T>(n,symbol){

    switch(symbol){
        case 'E':
            availableNumbers = new list<int>{2,4,6,8};
            break;
        case 'O':
            availableNumbers = new list<int>{1,3,5,7,9};
            break;
        default:
            throw runtime_error("wrong symbol passed");
    }

    this->symbol = * availableNumbers->begin();
}

template<typename T>
NumericalTTT_Player<T>::NumericalTTT_Player(std::string n, T symbol) :
        NumericalTTT_CommonPlayerFunctions<T>(n,symbol) {

}

template<typename T>
bool NumericalTTT_Player<T>::isNumberAvailable(T number) {
    for (auto i : *this->availableNumbers){
        if (i == number){
            return true;
        }
    }
    return false;
}

template<typename T>
void NumericalTTT_Player<T>::getmove(int &x, int &y) {
    cout << "Enter your Move , x for the row, y for the column : " << endl;
    cin >> x >> y;
    cout << "Enter your next used number : " << endl;
    cin >> this->symbol;
    while(!this->isNumberAvailable(this->symbol)){
        cout << "number is not available, try something different" << endl;
        cin >> this->symbol;
    }
    this->RemoveUsedNumber(this->symbol);
}

/// end of NumericalTTT_Player ----------------------------------------------------|




template<typename T>
NumericalTTT_RandomPlayer<T>::NumericalTTT_RandomPlayer(string n,T symbol) :
        NumericalTTT_CommonPlayerFunctions<T>(n,symbol){
    dimension = 3;
    this->name = "Random Computer Player";

    srand(static_cast<unsigned int>(time(0)));
}



template<typename T>
void NumericalTTT_RandomPlayer<T>::getmove(int &x, int &y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;

    if (!this->availableNumbers->empty()) {
        auto it = this->availableNumbers->begin();
        advance(it,(rand() % this->availableNumbers->size()));
        this->symbol = *it;
        this->RemoveUsedNumber(this->symbol);
    }

    while (!this->boardPtr->update_board(x,y,this->symbol)){
        x = rand() % this->dimension;  // Random number between 0 and 2
        y = rand() % this->dimension;
    }
    this->boardPtr->update_board(x,y,0);


}


/// end of RandomPlayer Implementation -----------------------------------|


void RunBoardGame(){ // if you want to play the game in terminal
    int choice;

    Board<int> * board = new NumericalTTT_Board<int>();
    Player<int> * players[2];
    NumericalTTT_CommonPlayerFunctions<int> * players_copy[2];
    NumericalTTT_MinMaxPlayer<int> * ai_players[2];
    bool ai_1 = false;
    bool ai_2 = false;

    string player1,player2;


    cout << "Numerical Tic Tac Toe GameBoard5 \n";

    // Set up player 1
    cout << "Enter Player 1 name (numbers are odd (1,3,5,7,9) ): ";
    cin >> player1;
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. Smart Computer (AI)\n";
    cin >> choice;

    switch(choice){
        case 1:
            players_copy[0] = new NumericalTTT_Player<int>(player1,'O');
            break;
        case 2:
            players_copy[0] = new NumericalTTT_RandomPlayer<int>("Random Computer",'O');
            players_copy[0]->setBoard(board);
            break;
        case 3:
            ai_1 = true;
           break;
        default:
            break;
    }


    cout << "Enter Player 2 name (numbers are even (2,4,6,8) ): ";
    cin >> player2;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. Smart Computer (AI)\n";
    cin >> choice;

    switch(choice){
        case 1:
            players_copy[1] = new NumericalTTT_Player<int>(player2,'E');
            break;
        case 2:
            players_copy[1] = new NumericalTTT_RandomPlayer<int>("Random Computer",'E');
            players_copy[1]->setBoard(board);
            break;
        case 3:
            ai_2 = true;
            break;
        default:
            break;
    }

    players[0] = players_copy[0];
    players[1] = players_copy[1];

    if (ai_1 && ai_2){
        ai_players[0] = new NumericalTTT_MinMaxPlayer<int>('O');
        ai_players[1] = new NumericalTTT_MinMaxPlayer<int>('E');

        ai_players[0]->setBoard(board);
        ai_players[1]->setBoard(board);

        ai_players[0]->SetOpponentNumbers(&ai_players[1]->GetAvailableNumbers());
        ai_players[1]->SetOpponentNumbers(&ai_players[0]->GetAvailableNumbers());
        players[0] = ai_players[0];
        players[1] = ai_players[1];
    }

    else if (ai_1){
        ai_players[0] = new NumericalTTT_MinMaxPlayer<int>('O');

        ai_players[0]->setBoard(board);

        ai_players[0]->SetOpponentNumbers(players_copy[1]->getAvailableNumbers());
        players[0] = ai_players[0];
    }

    else if (ai_2){
        ai_players[1] = new NumericalTTT_MinMaxPlayer<int>('E');

        ai_players[1]->setBoard(board);


        ai_players[1]->SetOpponentNumbers(players_copy[0]->getAvailableNumbers());
        players[1] = ai_players[1];
    }




    GameManager<int> fourInRowGameManager(board, players);

    fourInRowGameManager.run();

    delete board;

    for (auto & player : players){
        delete player;
    }
}


/// Implementation of the Wrapper class

bool BoardGame5_Wrapper::isInitialized() {
    return board != nullptr || players[0] != nullptr || players[1] != nullptr;
}

void
BoardGame5_Wrapper::InitializeGame(std::string player1, std::string player2, BoardGame5_Wrapper::PlayerType player1Type,
                                   BoardGame5_Wrapper::PlayerType player2Type) {
    board = new NumericalTTT_Board<int>();
    NumericalTTT_CommonPlayerFunctions<int> * players_copy[2];
    NumericalTTT_MinMaxPlayer<int> * ai_players[2];
    bool ai_1 = false;
    bool ai_2 = false;

    playersType[0] = player1Type;
    playersType[1] = player2Type;

    switch(player1Type){
        case Human:
            players_copy[0] = new NumericalTTT_Player<int>(player1,'O');
            break;
        case Randomizer:
            players_copy[0] = new NumericalTTT_RandomPlayer<int>("Random Computer",'O');
            players_copy[0]->setBoard(board);
            break;
        case AI:
            ai_1 = true;
            break;
        default:
            throw runtime_error("Error Occurred at line 462");
    }


    switch(player2Type){
        case Human:
            players_copy[1] = new NumericalTTT_Player<int>(player2,'E');
            break;
        case Randomizer:
            players_copy[1] = new NumericalTTT_RandomPlayer<int>("Random Computer",'E');
            players_copy[1]->setBoard(board);
            break;
        case AI:
            ai_2 = true;
            break;
        default:
            break;
    }

    players[0] = players_copy[0];
    players[1] = players_copy[1];

    if (ai_1 && ai_2){
        ai_players[0] = new NumericalTTT_MinMaxPlayer<int>('O');
        ai_players[1] = new NumericalTTT_MinMaxPlayer<int>('E');

        ai_players[0]->setBoard(board);
        ai_players[1]->setBoard(board);

        ai_players[0]->SetOpponentNumbers(&ai_players[1]->GetAvailableNumbers());
        ai_players[1]->SetOpponentNumbers(&ai_players[0]->GetAvailableNumbers());
        players[0] = ai_players[0];
        players[1] = ai_players[1];
    }

    else if (ai_1){
        ai_players[0] = new NumericalTTT_MinMaxPlayer<int>('O');

        ai_players[0]->setBoard(board);

        ai_players[0]->SetOpponentNumbers(players_copy[1]->getAvailableNumbers());
        players[0] = ai_players[0];
    }

    else if (ai_2){
        ai_players[1] = new NumericalTTT_MinMaxPlayer<int>('E');

        ai_players[1]->setBoard(board);


        ai_players[1]->SetOpponentNumbers(players_copy[0]->getAvailableNumbers());
        players[1] = ai_players[1];
    }

}

int **BoardGame5_Wrapper::GetBoard() {
    if (!this->isInitialized()){
        throw runtime_error("Game is Not initialized ");
    }
    return board->GetBoardNumbers();
}

int BoardGame5_Wrapper::GetMovesPlayed() {
    if (!this->isInitialized()){
        throw runtime_error("Game is Not initialized ");
    }
    return board->GetMovesPlayed();
}

vector<int> BoardGame5_Wrapper::GetAvailableNumbersForPlayer1() {
    if (!this->isInitialized()){
        throw runtime_error("Game is Not initialized ");
    }
    vector<int> result;
    list <int> * myList = nullptr;
    switch(playersType[0]){
        case Human:
            myList = dynamic_cast<NumericalTTT_Player<int>*>(players[0])->getAvailableNumbers();
            for(auto it : *myList){
                result.push_back(it);
            }
            break;
        case Randomizer:
            myList = dynamic_cast<NumericalTTT_RandomPlayer<int>*>(players[0])->getAvailableNumbers();
            for(auto it : *myList){
                result.push_back(it);
            }
            return result;
        case AI:
            myList = &(dynamic_cast<NumericalTTT_MinMaxPlayer<int>*>(players[0])->GetAvailableNumbers());
            for(auto it : *myList){
                result.push_back(it);
            }
            return result;
        default:
            throw runtime_error("Error Occurred inside GetAvailableNumbersForPlayer1 in line 558");
    }


    return result;

}


vector<int> BoardGame5_Wrapper::GetAvailableNumbersForPlayer2() {
    if (!this->isInitialized()){
        throw runtime_error("Game is Not initialized ");
    }
    vector<int> result;
    list <int> * myList = nullptr;
    switch(playersType[1]){
        case Human:
            myList = dynamic_cast<NumericalTTT_Player<int>*>(players[1])->getAvailableNumbers();
            for(auto it : *myList){
                result.push_back(it);
            }
            break;
        case Randomizer:
            myList = dynamic_cast<NumericalTTT_RandomPlayer<int>*>(players[1])->getAvailableNumbers();
            for(auto it : *myList){
                result.push_back(it);
            }
            return result;
        case AI:
            myList = &(dynamic_cast<NumericalTTT_MinMaxPlayer<int>*>(players[1])->GetAvailableNumbers());
            for(auto it : *myList){
                result.push_back(it);
            }
            return result;
        default:
            throw runtime_error("Error Occurred inside GetAvailableNumbersForPlayer2 in line 593");
    }


    return result;

}


string BoardGame5_Wrapper::GetPlayer1Name() {
    if (!this->isInitialized()){
        throw runtime_error("Game is Not initialized ");
    }
    return players[0]->getname();
}


string BoardGame5_Wrapper::GetPlayer2Name() {
    if (!this->isInitialized()){
        throw runtime_error("Game is Not initialized ");
    }
    return players[1]->getname();
}

void BoardGame5_Wrapper::GetPlayer1Move(int &x, int &y,int &symbol) {
    if (!this->isInitialized()){
        throw runtime_error("Game is Not initialized ");
    }

    if (playersType[0]){
        // pass since we will control the flow of this inside the UI
        return;
    }

    players[0]->getmove(x,y);
    symbol = players[0]->getsymbol();
}



void BoardGame5_Wrapper::GetPlayer2Move(int &x, int &y,int &symbol) {
    if (!this->isInitialized()){
        throw runtime_error("Game is Not initialized ");
    }

    if (playersType[1]){
        // pass since we will control the flow of this inside the UI
        return;
    }

    players[1]->getmove(x,y);
    symbol = players[1]->getsymbol();
}

void BoardGame5_Wrapper::Player1PerformMove(int x, int y) {
    if (!this->isInitialized()){
        throw runtime_error("Game is Not initialized ");
    }

    switch(playersType[0]){
        case Human:
            if (!board->update_board(x,y,players[0]->getsymbol())){
                throw runtime_error("Move didn't performed since it's a bad move, line 655 in Player1PerformMove");
            }
            dynamic_cast<NumericalTTT_Player<int>*>(players[0])->RemoveUsedNumber(players[0]->getsymbol());
            break;
        case Randomizer:
            if (!board->update_board(x,y,players[0]->getsymbol())){
                throw runtime_error("Move didn't performed since it's a bad move, line 661 in Player1PerformMove");
            }
            dynamic_cast<NumericalTTT_RandomPlayer<int>*>(players[0])->RemoveUsedNumber(players[0]->getsymbol());
            break;
        case AI:
            if (!board->update_board(x,y,players[0]->getsymbol())){
                throw runtime_error("Move didn't performed since it's a bad move, line 667 in Player1PerformMove");
            }
            dynamic_cast<NumericalTTT_MinMaxPlayer<int>*>(players[0])->RemoveUsedNumberFromPlayerList(players[0]->getsymbol());
            break;
        default:
            throw runtime_error("Error Occurred inside Player1PerformMove in line 672");
    }
}



void BoardGame5_Wrapper::Player2PerformMove(int x, int y) {
    if (!this->isInitialized()){
        throw runtime_error("Game is Not initialized ");
    }

    switch(playersType[1]){
        case Human:
            if (!board->update_board(x,y,players[1]->getsymbol())){
                throw runtime_error("Move didn't performed since it's a bad move, line 686 in Player2PerformMove");
            }
            dynamic_cast<NumericalTTT_Player<int>*>(players[1])->RemoveUsedNumber(players[1]->getsymbol());
            break;
        case Randomizer:
            if (!board->update_board(x,y,players[1]->getsymbol())){
                throw runtime_error("Move didn't performed since it's a bad move, line 692 in Player2PerformMove");
            }
            dynamic_cast<NumericalTTT_RandomPlayer<int>*>(players[1])->RemoveUsedNumber(players[1]->getsymbol());
            break;
        case AI:
            if (!board->update_board(x,y,players[1]->getsymbol())){
                throw runtime_error("Move didn't performed since it's a bad move, line 698 in Player2PerformMove");
            }
            dynamic_cast<NumericalTTT_MinMaxPlayer<int>*>(players[1])->RemoveUsedNumberFromPlayerList(players[1]->getsymbol());
            break;
        default:
            throw runtime_error("Error Occurred inside GetPlayer2Numbers in line 703");
    }

}


bool BoardGame5_Wrapper::isWin() {
    return board->is_win();
}

bool BoardGame5_Wrapper::isDraw() {
    return board->is_draw();
}

bool BoardGame5_Wrapper::isGameOver() {
    return board->game_is_over();
}

void BoardGame5_Wrapper::ClearGameState() {
    if (isInitialized()){
        delete board;
        board = nullptr; // Now safe to check if the board is initialized

        delete players[0];
        players[0] = nullptr;

        delete players[1];
        players[1] = nullptr;
    }
}

BoardGame5_Wrapper::~BoardGame5_Wrapper(){
    ClearGameState();
}






#endif //CUSTOMBOARDGAMESAPPLICATION_NUMERICAL_TIC_TAC_TOE_H
