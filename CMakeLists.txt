cmake_minimum_required(VERSION 3.27)

set(This CustomBoardGamesApplication)

project(CustomBoardGamesApplication C CXX)



set(CMAKE_CXX_STANDARD 17)

set(Source
        main.cpp
)

set(Headers
        AssignmentDemo_WithBouns/BoardGame_Classes.h

)

add_executable(
        ${This}
        ${Source}
        ${Headers}
)
