cmake_minimum_required(VERSION 3.27)

set(This CustomBoardGamesApplication)

project(CustomBoardGamesApplication C CXX)



set(CMAKE_CXX_STANDARD 17)

set(Source
        main.cpp
)

set(Headers
        AssignmentDemo_WithBouns/BoardGame_Classes.h
        BoardGame_2/Four_in_a_Row.h
        BoardGame_2/MinMax_FourInRow.h
        BoardGame_8/Ultimate_Tic-Tac-Toe.h
        BoardGame_8/Edited_3x3_XO.h
        Setup_games/games.h
        "BoardGame_1/Pyramic Tic-Tac-Toe.h"
        BoardGame_3/5x5X_O.h
        BoardGame_4/Word_Tic-Tac-Toe.h
        BoardGame_5/Numerical_Tic_Tac_Toe.h
        BoardGame_6/Inverse3_3_X_O.h
        BoardGame_7/FourByFourTicTacToe.h

)

add_executable(
        ${This}
        ${Source}
        ${Headers}
)
