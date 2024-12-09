#include <iostream>

#include "AssignmentDemo_WithBouns/Ultimate_Tic-Tac-Toe.h"
using namespace std;

int main() {
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
                delete players[0];
                delete players[1];
                return 0;
            }

            if (Grid.is_draw()) {
                cout << "It's a draw!\n";
                delete players[0];
                delete players[1];
                return 0;
            }
        }
    }

    delete players[0];
    delete players[1];
    return 0;
}

