#include "Setup_games/games.h"

using namespace std;

int main() {
    int choice;
    cout << "Welcome to BoardGames Application\n";
    cout<<"What Game do you want to play ? \n";
    cout<<"1-Pyramid Tic-Tac-Toe \n";
    cout<<"2-Four in a row Tic-Tac-Toe \n";
    cout<<"3-5X5 Tic-Tac-Toe \n";
    cout<<"4-Word Tic-Tac-Toe \n";
    cout<<"5-Numerical Tic-Tac-Toe \n";
    cout<<"6-Inverse Tic-Tac-Toe \n";
    cout<<"7-Four by Four Tic-Tac-Toe \n";
    cout<<"8-Ultimate Tic-Tac-Toe \n";

    cin>>choice;

    switch(choice) {
        case 1:
            RunBoardGame1();
            break;
        case 2:
            RunBoardGame2();
            break;
        case 3:
            RunBoardGame3();
            break;
        case 4:
            RunBoardGame4();
            break;
        case 5:
            RunBoardGame5();
            break;
        case 6:
            RunBoardGame6();
            break;
        case 7:
            RunBoardGame7();
            break;
        case 8:
            RunBoardGame8();
            break;
        default:
            cout << "Invalid choice, Try Again\n";
            break;
    }

    return 0;
}


