
#ifndef CUSTOMBOARDGAMESAPPLICATION_GAMES_H
#define CUSTOMBOARDGAMESAPPLICATION_GAMES_H
#include "../BoardGame_1/Pyramic Tic-Tac-Toe.h"
#include "../BoardGame_2/Four_in_a_Row.h"
#include "../BoardGame_3/5x5X_O.h"
#include "../BoardGame_4/Word_Tic-Tac-Toe.h"
#include "../BoardGame_5/Numerical_Tic_Tac_Toe.h"
#include "../BoardGame_7/FourByFourTicTacToe.h"
#include "../BoardGame_8/Ultimate_Tic-Tac-Toe.h"
#include "../BoardGame_6/Inverse3_3_X_O.h"

class BoardSetup{

   static void RunBoardGame1();
   static void RunBoardGame2();
   static void RunBoardGame3();
   static void RunBoardGame4();
   static void RunBoardGame5();
   static void RunBoardGame6();
   static void RunBoardGame7();
   static void RunBoardGame8();

};

void RunBoardGame1() {

    int choice;

    Board<char> * board = new Pyramid_grid<char>();
    Player<char> * players[2];

    string player1,player2;


    cout << "Pyramid Tic-Tac-Toe, GameBoard1 \n";

    // Set up player 1
    cout << "Enter Player 1 name (symbol is X): ";
    cin >> player1;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice){
        case 1:
            players[0] = new Pyramid_player<char>(player1,'X');
            break;
        case 2:
            players[0] = new Pyramid_Random_Player<char>('X');
            players[0]->setBoard(board);
            break;
        default:
            break;
    }


    cout << "Enter Player 2 name (symbol is O): ";
    cin >> player2;
    cout << "Choose Player O type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice){
        case 1:
            players[1] = new Pyramid_player<char>(player2,'O');
            break;
        case 2:
            players[1] = new Pyramid_Random_Player<char>('O');
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

}

void RunBoardGame3() {
    int choice;

    Board<char> * board = new FiveByFive_Board<char>();
    Player<char> * players[2];

    string player1,player2;


    cout << "Five by Five XO GameBoard3 \n";

    // Set up player 1
    cout << "Enter Player 1 name (symbol is X): ";
    cin >> player1;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice){
        case 1:
            players[0] = new FiveByFive_HumanPlayer<char>(player1,'X');
            players[0]->setBoard(board);
            break;
        case 2:
            players[0] = new FiveByFive_RandomPlayer<char>('X');
            players[0]->setBoard(board);
            break;

        default:
            break;
    }


    cout << "Enter Player 2 name (symbol is O): ";
    cin >> player2;
    cout << "Choose Player O type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice){
        case 1:
            players[1] = new FiveByFive_HumanPlayer<char>(player2,'O');
            players[1]->setBoard(board);
            break;
        case 2:
            players[1] = new FiveByFive_RandomPlayer<char>('O');
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
}

void RunBoardGame2() {
    int choice;

    Board<char> * board = new Four_in_a_Row_Board<char>();
    Player<char> * players[2];

    string player1,player2;


    cout << "Four in a Row GameBoard2 \n";

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
            players[0]->setBoard(board);
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
            players[1]->setBoard(board);
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
}

void RunBoardGame4() {
    int choice;

    Board<char> * board = new Word_grid<char>();
    Player<char> * players[2];

    string player1,player2;


    cout << "Word Grid GameBoard4 \n";

    cout << "Enter Player 1 name: ";
    cin >> player1;
    cout << "Choose Player type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice){
        case 1:
            players[0] = new Word_player<char>(player1,'X');
            break;
        case 2:
            players[0] = new Word_Random_Player<char>('X');
            players[0]->setBoard(board);
            break;
        default:
            break;
    }


    cout << "Enter Player 2 name: ";
    cin >> player2;
    cout << "Choose Player type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice){
        case 1:
            players[1] = new Word_player<char>(player2,'O');
            break;
        case 2:
            players[1] = new Word_Random_Player<char>('O');
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
}

void RunBoardGame5() {
    int choice;

    Board<int> * board = new NumericalTTT_Board<int>();
    Player<int> * players[2];
    NumericalTTT_CommonPlayerFunctions<int> * players_copy[2];
    NumericalTTT_MinMaxPlayer<int> * ai_players[2];
    bool ai_1 = false;
    bool ai_2 = false;

    string player1,player2;


    cout << "Numerical Tic Tac Toe GameBoard5 \n";

    cout << "Enter Player 1 name (numbers are odd (1,3,5,7,9) ): ";
    cin >> player1;
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. Smart Computer (AI)\n";
    cin >> choice;

    switch(choice){
        case 1:
            players_copy[0] = new NumericalTTT_Player<int>(player1,'O'); // O here means ODD
            break;
        case 2:
            players_copy[0] = new NumericalTTT_RandomPlayer<int>("Random Computer",'O'); // O here means ODD
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


    // the following approach for making the ai is because i want each ai player to have a reference to the other
    // player numbers list, i can only achieve that when the player finished full player choosing
    // another reason for using a players_copy is the need for using some methods in the players class itself
    // that is not available in the player abstract class
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

void RunBoardGame6() {
    int choice;

    Board<char> * board = new ThreeByThree_Board<char>();
    Player<char> * players[2];

    string player1,player2;


    cout << "Inverse Tic_Tac_Toe GameBoard6 \n";

    cout << "Enter Player 1 name (symbol is X): ";
    cin >> player1;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice){
        case 1:
            players[0] = new ThreeByThree_HumanPlayer<char>(player1,'X');
            players[0]->setBoard(board);
            break;
        case 2:
            players[0] = new ThreeByThree_RandomPlayer<char>('X');
            players[0]->setBoard(board);
            break;

        default:
            break;
    }


    cout << "Enter Player 2 name (symbol is O): ";
    cin >> player2;
    cout << "Choose Player O type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice){
        case 1:
            players[1] = new ThreeByThree_HumanPlayer<char>(player2,'O');
            players[1]->setBoard(board);
            break;
        case 2:
            players[1] = new ThreeByThree_RandomPlayer<char>('O');
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
}

void RunBoardGame7() {
    int choice;

    // the reason for using shared pointer is the need for each token to have the same reference to the board
    // since iam making each token have the responsability to change its position on the board
    Player<Token> * players[2];

    auto boardPtr = std::make_shared<FourByFourTTT_Board<Token>>();

    auto emptyToken1 = std::make_shared<Token>();
    emptyToken1->InitializeData({0, 0}, 'X', boardPtr);

    auto emptyToken2 = std::make_shared<Token>();
    emptyToken2->InitializeData({0, 0}, 'O', boardPtr);

    string player1,player2;


    cout << "Four by Four Tic Tac Toe GameBoard7\n";

    cout << "Enter Player 1 name (symbol is X): ";
    cin >> player1;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
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

        default:
            break;
    }

    cout << "Enter Player 2 name (symbol is O): ";
    cin >> player2;
    cout << "Choose Player O type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
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

        default:
            break;
    }

    GameManager<Token> fourInRowGameManager(boardPtr.get(),players);

    fourInRowGameManager.run();

    for (auto & player : players){
        delete player;
    }
}

void RunBoardGame8() {
    int choice;

    Board<char> * board = new Ultimate_grid<char>();
    Player<char> * players[2];

    string player1,player2;


    cout << "Ultimate tic-tac-toe  \n";

    cout << "Enter Player 1 name (symbol is X): ";
    cin >> player1;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice){
        case 1:
            players[0] = new Ultimate_Player<char>(player1,'X');
            break;
        case 2:
            players[0] = new Ultimate_Random_Player<char>('X');
            players[0]->setBoard(board);
            break;

        default:
            break;
    }


    cout << "Enter Player 2 name (symbol is O): ";
    cin >> player2;
    cout << "Choose Player O type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice){
        case 1:
            players[1] = new Ultimate_Player<char>(player2,'O');
            break;
        case 2:
            players[1] = new Ultimate_Random_Player<char>('O');
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
}


#endif
