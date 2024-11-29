

#ifndef CUSTOMBOARDGAMESAPPLICATION_MINMAX_FOURINROW_H
#define CUSTOMBOARDGAMESAPPLICATION_MINMAX_FOURINROW_H

#include "../AssignmentDemo_WithBouns/BoardGame_Classes.h"
#include <algorithm>
#include <limits>

template<typename T>
class FourInRowMinMax : public Player<T>{
public:
    FourInRowMinMax(T symbol,T opponentSymbol);
    void getmove(int &x,int &y) override;
    bool IsSearchingForMove();
private:
    bool isSearchingForMove;
    T opponentSymbol;
    int GetBestMove();
    int CalculateMinMax(T s,bool isMaxmizing,int depth);
};


template<typename T>
FourInRowMinMax<T>::FourInRowMinMax(T symbol,T opponentSymbol) : Player<T>(symbol){
    this->opponentSymbol = opponentSymbol;
    this->name = "Ai Player";
}

template<typename T>
void FourInRowMinMax<T>::getmove(int &x, int &y) {
    y = GetBestMove();
}


template<typename T>
int FourInRowMinMax<T>::GetBestMove() {
    isSearchingForMove = true;
    cout << "Searching for a Move" << endl;
    int bestMove = -3;
    int bestValue = numeric_limits<int>::min();

    // Checking for immediate win

    for (int j = 0 ; j < 7 ; j++){
        if (this->boardPtr->update_board(0,j,this->symbol)){
            if (this->boardPtr->is_win()){
                this->boardPtr->update_board(0,j,0);
                return j;
            }
            this->boardPtr->update_board(0,j,0);
        }
    }


    // Checking for opponent wins to block it

    for (int j = 0 ; j < 7 ; j++){
        if (this->boardPtr->update_board(0,j,this->opponentSymbol)){
            if (this->boardPtr->is_win()){
                this->boardPtr->update_board(0,j,0);
                return j;
            }
            this->boardPtr->update_board(0,j,0);
        }
    }




    for (int j = 0 ; j < 7 ; j++){
        if (this->boardPtr->update_board(0,j,this->symbol)){
            int nextMove = CalculateMinMax(this->symbol,false, 8);
            this->boardPtr->update_board(0,j,0);
            if (nextMove > bestValue){
                bestMove = j;
                bestValue = nextMove;
            }

        }
    }


    if (bestMove == -3){
        cerr << "couldn't find a best move ERROR " << endl;
    }
    isSearchingForMove = false;
    cout << "Found a Move" << endl;
    return bestMove;
}

template<typename T>
bool FourInRowMinMax<T>::IsSearchingForMove() {
    return isSearchingForMove;
}


template<typename T>
int FourInRowMinMax<T>::CalculateMinMax(T s, bool isMaxmizing,int depth) {
    if (this->boardPtr->is_win()){
        return isMaxmizing ? -1 : 1;
    }
    else if (this->boardPtr->is_draw() || depth <= 0){
        return 0;
    }

    int bestValue = isMaxmizing ? numeric_limits<int>::min() : numeric_limits<int>::max();


    for (int j = 0 ; j < 7 ; j++){
        if (this->boardPtr->update_board(0,j,s)){
            int nextMove = CalculateMinMax(isMaxmizing ? this->opponentSymbol : this->symbol,!isMaxmizing,depth - 1);
            this->boardPtr->update_board(0,j,0);

            if (isMaxmizing){
                bestValue = max(bestValue,nextMove);
            }
            else{
                bestValue = min(bestValue,nextMove);
            }
        }
    }


    return bestValue;

}




#endif //CUSTOMBOARDGAMESAPPLICATION_MINMAX_FOURINROW_H
