
#ifndef CUSTOMBOARDGAMESAPPLICATION_FOURBYFOURTICTACTOE_H
#define CUSTOMBOARDGAMESAPPLICATION_FOURBYFOURTICTACTOE_H

#include "../AssignmentDemo_WithBouns/BoardGame_Classes.h"
#include <cmath>
#include <memory>
#include <utility>


template<typename T>
class FourByFourTTT_Board : public Board<T>{
private:

public:
    bool isValidMove(int x,int y,T token);

    FourByFourTTT_Board();

    bool update_board(int x, int y, T token) override;

    void display_board() override;

    bool is_win() override;

    bool is_draw() override;

    bool game_is_over() override;

    T ** GetBoard(); // need to be changed since iam using a tokens class

    T * GetTokenAtPosition(int x, int y);

    int GetNumberOfMoves();
};

template<typename T>
class FourByFourTTT_Player : public Player<T>{
public:
    FourByFourTTT_Player(string n, T symbol);


    void getmove(int &x, int &y) override;
};

template<typename T>
class FourByFourTTT_RandomPlayer : public RandomPlayer<T>{
private:
    pair<int,int> lastPositionPlayed;
    vector<T*> tokensReference;
    vector<pair<int,int>> GetPossibleValidMoves(pair<int, int> currentPosition);
    char playerSymbol;
    void UpdateReferences();
public:
    FourByFourTTT_RandomPlayer(T token,Board<T> * boardForInitialization);

    void getmove(int &x,int & y) override;
};

class Token{
public:
    pair<int,int> currentPosition;
    vector<pair<int,int>> previousMoves;
    char symbol;
    shared_ptr<FourByFourTTT_Board<Token>>  boardPtr;


    Token() : currentPosition({0, 0}), symbol(' '), boardPtr() {
    }

    void Reset(){
        symbol = ' ';
        previousMoves.clear();
    }

    void InitializeData(pair<int,int> position, char s, shared_ptr<FourByFourTTT_Board<Token>>  bPtr){
        currentPosition = position;
        symbol = s;
        this->boardPtr = std::move(bPtr);
    }

    void SetPosition(pair<int,int> position){
        previousMoves.push_back(currentPosition);
        int previousX = currentPosition.first;
        int previousY = currentPosition.second;

        Token nullVariable;
        nullVariable.InitializeData({previousX,previousY},' ',boardPtr);
        currentPosition = position;

        boardPtr->GetBoard()[currentPosition.first][currentPosition.second] = *this;
        boardPtr->GetBoard()[previousX][previousY] = nullVariable;



    }



    void SetSymbol(char s){
        symbol = s;
    }

    bool GetBackToPreviousMove(){
        if (previousMoves.empty()){
            cerr << "previous Moves is empty care " << endl;
            return false;
        }
        int currentX = currentPosition.first;
        int currentY = currentPosition.second;

        currentPosition = previousMoves.back();

        if (boardPtr->GetBoard()[currentPosition.first][currentPosition.second].GetSymbol() != ' '){
            throw runtime_error("Attempting to get back to a place where it already having a Token, line 97");
        }

        previousMoves.pop_back();


        boardPtr->GetBoard()[currentPosition.first][currentPosition.second] = *this; // by doing this, this instance of class now at the previous position

        boardPtr->GetBoard()[currentX][currentY].Reset();

        currentPosition.first = currentX; // this current position now is being own by the empty place on the board
        currentPosition.second = currentY;



        return true;
    }

    pair<int,int> GetCurrentPosition() const{
        return currentPosition;
    }

    char GetSymbol() const{
        return symbol;
    }

    Token(const Token& other) {
       this->currentPosition = other.currentPosition;
       this->symbol = other.symbol;
       this->previousMoves = other.previousMoves;
       this->boardPtr = other.boardPtr;  // Copy the shared_ptr
    }

    Token& operator=(const Token& other) {
        if (this != &other) {
            this->currentPosition = other.currentPosition;
            this->symbol = other.symbol;
            this->previousMoves = other.previousMoves;
        }

        return *this;
    }

    bool operator==(const Token & other) const{
        return (currentPosition == other.currentPosition && this->symbol == other.symbol);
    }

    bool operator!=(const Token & other) const{
        return !(*this == other);
    }



};


///###############################################################
///###################### Board Implementation ###################
///###############################################################

template<typename T>
FourByFourTTT_Board<T>::FourByFourTTT_Board() {
    this->rows = this->columns = 4;
    this->board = new Token*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new Token[this->columns];
        for (int j = 0; j < this->columns; j++) {
            auto boardPtr = std::shared_ptr<FourByFourTTT_Board<Token>>(this);
            this->board[i][j].InitializeData({i, j}, ' ', boardPtr);
        }
    }
    this->n_moves = 0;

    this->board[0][0].SetSymbol('O');
    this->board[0][2].SetSymbol('O');
    this->board[3][1].SetSymbol('O');
    this->board[3][3].SetSymbol('O');
    this->board[0][1].SetSymbol('X');
    this->board[0][3].SetSymbol('X');
    this->board[3][0].SetSymbol('X');
    this->board[3][2].SetSymbol('X');
}

template<typename T>
void FourByFourTTT_Board<T>::display_board() {
    cout << "    0   1   2   3  \n";  // Column headers
    cout << "  +---+---+---+---+\n";  // Top border
    for (int i = 0; i < 4; i++) {
        cout << i << " |";  // Row number
        for (int j = 0; j < 4; j++) {
            cout << " " << this->board[i][j].symbol << " |";  // Board cells with vertical borders
        }
        cout << "\n  +---+---+---+---+\n";  // Row divider
    }
}

template<typename T>
bool FourByFourTTT_Board<T>::is_win() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {  // Check from columns 0, 1 only for 3 in a row
            if (this->board[i][j].symbol != ' ' &&
                this->board[i][j].symbol == this->board[i][j + 1].symbol &&
                this->board[i][j + 1].symbol == this->board[i][j + 2].symbol) {
                return true;  // Winner found in row
            }
        }
    }

    // Check columns
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {  // Check from rows 0, 1 only for 3 in a column
            if (this->board[j][i].symbol != ' ' &&
                this->board[j][i].symbol == this->board[j + 1][i].symbol &&
                this->board[j + 1][i].symbol == this->board[j + 2][i].symbol) {
                return true;  // Winner found in column
            }
        }
    }

    for (int i = 0 ; i < 2 ; i++){
        for (int j = 0; j < 2; j++) {
            if (this->board[i][j].symbol != ' ' &&
                this->board[i][j].symbol == this->board[i + 1][j + 1].symbol &&
                this->board[i + 1][j + 1].symbol == this->board[i + 2][j + 2].symbol) {
                return true;
            }
        }
    }


    for (int i = 0 ; i < 2 ; i++){
        for (int j = 0; j < 2; j++) {
            if (this->board[i][3 - j].symbol != ' ' &&
                this->board[i][3 - j].symbol == this->board[i + 1][3 - (j + 1)].symbol &&
                this->board[i + 1][3 - (j + 1)].symbol == this->board[i + 2][3 - (j + 2)].symbol) {
                return true;
            }
        }
    }


    return false;
}

template<typename T>
bool FourByFourTTT_Board<T>::is_draw() {
    return false; // it's impossible to have a draw in this game description
}

template<typename T>
bool FourByFourTTT_Board<T>::game_is_over() {
    return is_win();
}

template<typename T>
T **FourByFourTTT_Board<T>::GetBoard() {
    return this->board;
}

template<typename T>
int FourByFourTTT_Board<T>::GetNumberOfMoves() {
    return this->n_moves;
}


template<typename T>
bool FourByFourTTT_Board<T>::update_board(int x, int y, T token) {
    if (isValidMove(x,y,token)){
        if (token.GetSymbol() == ' '){
            return this->board[x][y].GetBackToPreviousMove();
        }
        else{
            token.SetPosition({x, y});
            return true;
        }
    }
    return false;
}

template<typename T>
bool FourByFourTTT_Board<T>::isValidMove(int x, int y, T token) {
    bool isValid1 = !(x < 0 || x >= this->rows || y < 0 || y >= this->columns);
    if (token.GetSymbol() == ' ' && isValid1){
        return true;
    }
    if (isValid1){
        int currentX = token.GetCurrentPosition().first;
        int currentY = token.GetCurrentPosition().second;
        bool isValid2 = this->board[x][y].GetSymbol() == ' ' &&
                 (abs(currentX - x) == 1 || abs(currentY - y) == 1) &&
                (abs(currentX - x) != abs(currentY - y) );

        return isValid2;
    }
    return false;
}

template<typename T>
T *FourByFourTTT_Board<T>::GetTokenAtPosition(int x, int y) {
    return &(this->board[x][y]);
}

///########################################################################
///###################### Board Implementation Finished ###################
///########################################################################


///################################################################
///###################### Player Implementation ###################
///################################################################

template<typename T>
FourByFourTTT_Player<T>::FourByFourTTT_Player(string n,T symbol) : Player<T>(n,symbol){}

template<typename T>
void FourByFourTTT_Player<T>::getmove(int &x, int &y) {
    int tokenPositionX, tokenPositionY;
    auto * FourByFourBoard = dynamic_cast<FourByFourTTT_Board<Token>*>(this->boardPtr);
    cout << "Chose the token you want to move by selecting it's position : " << endl;
    cin >> tokenPositionX >> tokenPositionY;
    auto tokenPtr = FourByFourBoard->GetTokenAtPosition(tokenPositionX,tokenPositionY);

    while(tokenPtr->GetSymbol() != this->symbol.GetSymbol()){
        cout << "invalid Token Choose, select a Token that matches your character  : " << endl;
        cin >> tokenPositionX >> tokenPositionY;
        tokenPtr = FourByFourBoard->GetTokenAtPosition(tokenPositionX,tokenPositionY);
    }

    cout << "Where you want to move it (one adjacent move that is not bigger than 1 tile)" << endl;
    cin >> x >> y;
    while(!FourByFourBoard->isValidMove(x,y,*tokenPtr)){
        cout << "Invalid Place Try again" << endl;
        cin >> x >> y;
    }

    this->symbol = *tokenPtr;
    this->symbol.boardPtr = tokenPtr->boardPtr;
}


///#########################################################################
///###################### Player Implementation Finished ###################
///#########################################################################



///#######################################################################
///###################### Random Player Implementation ###################
///#######################################################################

template<typename T>
FourByFourTTT_RandomPlayer<T>::FourByFourTTT_RandomPlayer(T token,Board<T> * boardForInitialization) : RandomPlayer<T>(token){
    this->name = "Random Player";
    this->dimension = 4;
    auto * FourByFourBoard = dynamic_cast<FourByFourTTT_Board<Token>*>(boardForInitialization);
    playerSymbol = token.GetSymbol();
    switch(token.GetSymbol()){
        case 'O':
            tokensReference.push_back(FourByFourBoard->GetTokenAtPosition(0,0));
            tokensReference.push_back(FourByFourBoard->GetTokenAtPosition(0,2));
            tokensReference.push_back(FourByFourBoard->GetTokenAtPosition(3,1));
            tokensReference.push_back(FourByFourBoard->GetTokenAtPosition(3,3));
            break;
        case 'X':
            tokensReference.push_back(FourByFourBoard->GetTokenAtPosition(0,1));
            tokensReference.push_back(FourByFourBoard->GetTokenAtPosition(0,3));
            tokensReference.push_back(FourByFourBoard->GetTokenAtPosition(3,0));
            tokensReference.push_back(FourByFourBoard->GetTokenAtPosition(3,2));
            break;
        default:
            throw runtime_error("some thing went wrong at randomPlayer class Board Game7");
    }



    srand(static_cast<unsigned int>(time(0)));
}

template<typename T>
void FourByFourTTT_RandomPlayer<T>::getmove(int &x, int &y) {
    UpdateReferences();
    auto * FourByFourBoard = dynamic_cast<FourByFourTTT_Board<Token>*>(this->boardPtr);
    auto randomToken = tokensReference[rand() % tokensReference.size()];

    vector<pair<int,int>> randomDirections = GetPossibleValidMoves(randomToken->GetCurrentPosition());
    vector<pair<int,int>> validRandomDirections;

    for (auto & i : randomDirections){
        if (FourByFourBoard->isValidMove(i.first,i.second,*randomToken)){
            validRandomDirections.push_back(i);
        }
    }

    pair<int,int> randomDirection = validRandomDirections[rand() % validRandomDirections.size()];

    x = randomDirection.first;
    y = randomDirection.second;


    lastPositionPlayed.first = x;
    lastPositionPlayed.second = y;


    this->symbol = *randomToken;
    this->symbol.boardPtr = randomToken->boardPtr;
}


template<typename T>
vector<pair<int, int>> FourByFourTTT_RandomPlayer<T>::GetPossibleValidMoves(pair<int,int> currentPosition) {
    vector<pair<int,int>> result;
    vector<pair<int,int>> directions = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

    for (auto dir : directions) {
        int newX = currentPosition.first + dir.first;
        int newY = currentPosition.second + dir.second;
        if (newX >= 0 && newX <= 3 && newY >= 0 && newY <= 3) {
            result.push_back({newX, newY});
        }
    }

    return result;
}

template<typename T>
void FourByFourTTT_RandomPlayer<T>::UpdateReferences() {
    auto * FourByFourBoard = dynamic_cast<FourByFourTTT_Board<Token>*>(this->boardPtr);

    for (int i = 0 ; i < tokensReference.size() ; i++){
        if (tokensReference[i]->GetSymbol() != playerSymbol){
            tokensReference[i] = FourByFourBoard->GetTokenAtPosition(lastPositionPlayed.first,lastPositionPlayed.second);
            tokensReference[i]->currentPosition = lastPositionPlayed;
        }
    }
}


void RunBoardGame(){
    int choice;

    Player<Token> * players[2];

    auto boardPtr = std::make_shared<FourByFourTTT_Board<Token>>();

    auto emptyToken1 = std::make_shared<Token>();
    emptyToken1->InitializeData({0, 0}, 'X', boardPtr);

    auto emptyToken2 = std::make_shared<Token>();
    emptyToken2->InitializeData({0, 0}, 'O', boardPtr);

    string player1,player2;


    cout << "Five by Five XO GameBoard3 \n";

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
            players[0] = new FourByFourTTT_Player<Token>(player1,*emptyToken1);
            players[0]->setBoard(boardPtr.get());
            break;
        case 2:
            players[0] = new FourByFourTTT_RandomPlayer<Token>(*emptyToken1,boardPtr.get());
            players[0]->setBoard(boardPtr.get());
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
            players[1] = new FourByFourTTT_Player<Token>(player2,*emptyToken2);
            players[1]->setBoard(boardPtr.get());
            break;
        case 2:
            players[1] = new FourByFourTTT_RandomPlayer<Token>(*emptyToken2,boardPtr.get());
            players[1]->setBoard(boardPtr.get());
            break;
        case 3:

            break;
        default:
            break;
    }

    GameManager<Token> fourInRowGameManager(boardPtr.get(),players);

    fourInRowGameManager.run();

    for (auto & player : players){
        delete player;
    }
}


#endif //CUSTOMBOARDGAMESAPPLICATION_FOURBYFOURTICTACTOE_H
