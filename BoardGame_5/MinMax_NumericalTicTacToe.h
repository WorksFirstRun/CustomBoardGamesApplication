
#ifndef CUSTOMBOARDGAMESAPPLICATION_MINMAX_NUMERICALTICTACTOE_H
#define CUSTOMBOARDGAMESAPPLICATION_MINMAX_NUMERICALTICTACTOE_H


#include "../AssignmentDemo_WithBouns/BoardGame_Classes.h"
#include <algorithm>
#include <limits>
#include <list>
#include <stack>

template<typename T>
class NumericalTTT_MinMaxPlayer : public Player<T>{
public:
    NumericalTTT_MinMaxPlayer(T symbol);

    void getmove(int &x, int &y) override;

    void SetOpponentNumbers(list<int> * o);

    list<int> & GetAvailableNumbers();

    void RemoveUsedNumberFromPlayerList(T number);

private:
    bool UndoMove(int x, int y,T s,bool isMaximising); // responsible for adding the symbol back to the list
    bool PlayMove(int x, int y,T s,bool isMaximising); // responsible for removing the symbol from the availableNumbers
    list<int> availableNumbers;
    list<int> * availableOpponentNumbers;
    vector<int> GetBestMove();
    int CalculateMinMax(T s,bool isMaximising,int depth);
};

template<typename T>
void NumericalTTT_MinMaxPlayer<T>::RemoveUsedNumberFromPlayerList(T number) {
    auto it = std::find(availableNumbers.begin(), availableNumbers.end(),number);
    if (it != availableNumbers.end()){
        availableNumbers.erase(it);
    }
}

template<typename T>
bool NumericalTTT_MinMaxPlayer<T>::PlayMove(int x, int y,T s,bool isMaximising) {
    list<int> * currentList = isMaximising ? availableOpponentNumbers : &availableNumbers;
    auto it = std::find(currentList->begin(), currentList->end(),s);
    if (it == currentList->end()){
        return false;
    }
    if (!this->boardPtr->update_board(x,y,s)){
        return false;
    }

    isMaximising? availableOpponentNumbers->erase(it) : availableNumbers.erase(it);
    return true;
}

template<typename T>
bool NumericalTTT_MinMaxPlayer<T>::UndoMove(int x, int y,T s,bool isMaximising) {
    /*this->boardPtr->display_board();*/
    if (!this->boardPtr->update_board(x,y,0)){
        return false;
    }
    /*this->boardPtr->display_board()*/;
    list<int> * currentList = isMaximising ? availableOpponentNumbers : &availableNumbers;
    auto it = std::find(currentList->begin(), currentList->end(),s);
    if (it == currentList->end()){
       /* isMaximising ?  availableOpponentNumbers->push_front(s) : availableNumbers.push_front(s);*/
        isMaximising ? availableOpponentNumbers->push_front(s) : availableNumbers.push_front(s);
    }

    return true;
}

template<typename T>
NumericalTTT_MinMaxPlayer<T>::NumericalTTT_MinMaxPlayer(T symbol): Player<T>(symbol) {
    this->name = "Ai Player";
    switch(symbol){
        case 'E':
            availableNumbers = {2,4,6,8};
            break;
        case 'O':
            availableNumbers = {1,3,5,7,9};
            break;
        default:
            cerr << "Wrong Symbol passed" << endl;
            break;
    }

    this->symbol = * availableNumbers.begin();
}

template<typename T>
vector<int> NumericalTTT_MinMaxPlayer<T>::GetBestMove() {
    int bestValue = std::numeric_limits<int>::min();
    vector<int> bestMove = {-1, -1,-1};

    auto it = availableNumbers.begin();
    for (int h = 0 ; h < availableNumbers.size() ; h++){
        it = availableNumbers.begin();
        advance(it,h);
        this->symbol = *it;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; ++j) {
                if (PlayMove(i,j,this->symbol,false)) {
                    if (this->boardPtr->is_win()) {
                        UndoMove(i,j,this->symbol, false);
                        return {i, j,this->symbol}; // Winning move found
                    }
                    UndoMove(i,j,this->symbol, false);
                }
            }
        }
    }

    this->symbol = *availableNumbers.begin();

    it = availableOpponentNumbers->begin();
    for (int h = 0 ; h < availableOpponentNumbers->size() ; h++){
        it = availableOpponentNumbers->begin();
        advance(it,h);
        this->symbol = *it;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; ++j) {
                if (PlayMove(i,j,this->symbol, true)) {
                    if (this->boardPtr->is_win()) {
                        UndoMove(i,j,this->symbol, true);
                        this->symbol = *availableNumbers.begin();
                        return {i, j,this->symbol};
                    }
                    UndoMove(i,j,this->symbol, true);
                }
            }
        }
    }

    it = availableNumbers.begin();
    for (int h = 0 ; h < availableNumbers.size() ; h++) {
        it = availableNumbers.begin();
        advance(it,h);
        this->symbol = *it;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (PlayMove(i,j,this->symbol, false)) {
                    int moveValue = CalculateMinMax(this->symbol, true,4);
                    UndoMove(i,j,this->symbol, false);

                    if (moveValue > bestValue) {
                        bestMove = {i, j,this->symbol};
                        bestValue = moveValue;
                    }
                }
            }
        }
    }

    return bestMove;
}

template<typename T>
int NumericalTTT_MinMaxPlayer<T>::CalculateMinMax(T s, bool isMaximising,int depth) {
    if (this->boardPtr->is_win()) {
        return isMaximising ? -1 : 1;
    } else if (this->boardPtr->is_draw() || depth <= 0) {
        return 0;
    }

    int bestValue = isMaximising ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    list<int> currentList = isMaximising ? *availableOpponentNumbers : availableNumbers;

    auto it = currentList.begin();
    for (int h = 0 ; h < currentList.size() ; h++){
        it = currentList.begin();
        advance(it,h);
        s = *it;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (PlayMove(i,j,s,isMaximising)) {
                    int value = CalculateMinMax(s, !isMaximising, depth - 1);
                    UndoMove(i,j,s,isMaximising); // Undo move

                    if (isMaximising) {
                        bestValue = std::max(bestValue, value);
                    } else {
                        bestValue = std::min(bestValue, value);
                    }
                }
            }
        }
    }

    return bestValue;
}

template<typename T>
void NumericalTTT_MinMaxPlayer<T>::getmove(int &x, int &y) {
    vector<int> bestMove = GetBestMove();
    x = bestMove[0];
    y = bestMove[1];
    this->symbol = bestMove[2];
    auto it = std::find(availableNumbers.begin(), availableNumbers.end(),this->symbol);
    availableNumbers.erase(it);
}

template<typename T>
list<int> & NumericalTTT_MinMaxPlayer<T>::GetAvailableNumbers() {
    return availableNumbers;
}

template<typename T>
void NumericalTTT_MinMaxPlayer<T>::SetOpponentNumbers(list<int> *o) {
    availableOpponentNumbers = o;
}


#endif //CUSTOMBOARDGAMESAPPLICATION_MINMAX_NUMERICALTICTACTOE_H
