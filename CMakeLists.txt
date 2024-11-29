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

)

add_executable(
        ${This}
        ${Source}
        ${Headers}
)
