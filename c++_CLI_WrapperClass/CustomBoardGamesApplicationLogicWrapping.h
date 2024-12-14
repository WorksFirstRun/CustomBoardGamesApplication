#pragma once
#include "pch.h"
#include "../BoardGame_1/Pyramic Tic-Tac-Toe.h"
#include "../BoardGame_2/Four_in_a_Row.h"
#include "../BoardGame_3/5x5X_O.h"
#include "../BoardGame_4/Word_Tic-Tac-Toe.h"
#include "../BoardGame_5/Numerical_Tic_Tac_Toe.h"
#include "../BoardGame_6/Inverse3_3_X_O.h"
#include "../BoardGame_7/FourByFourTicTacToe.h"
#include "../BoardGame_8/Ultimate_Tic-Tac-Toe.h"
#include <msclr/marshal_cppstd.h>

namespace CustomBoardGamesApplicationLogicWrapping {
    // Game 1: Pyramid Tic-Tac-Toe
    public ref class BoardGame1 {
    private:
        Pyramid_grid<char>* boardGame1Logic;
        bool disposed;
    public:
        enum class PlayerTypeBoardGame1 {
            Human,
            Random
        };

        BoardGame1();
        ~BoardGame1();
        !BoardGame1();

        void InitializeTheBoard_MC(String^ player1Name, String^ player2Name, 
                                 PlayerTypeBoardGame1 player1Type, PlayerTypeBoardGame1 player2Type);
        List<char>^ GetBoard_MC();
        int GetNumberOfMovesPlayed_MC();
        String^ GetPlayer1Name_MC();
        String^ GetPlayer2Name_MC();
        KeyValuePair<int, int>^ GetPlayer1Move_MC();
        KeyValuePair<int, int>^ GetPlayer2Move_MC();
        void Player1PerformMove_MC(int x, int y);
        void Player2PerformMove_MC(int x, int y);
        bool IsValidMove_MC(int x, int y);
        bool isWin_MC();
        bool isDraw_MC();
        bool isGameOver_MC();
        void ClearGameState_MC();
    };

    // Game 2: Four in a Row
    public ref class BoardGame2 {
    private:
        BoardGame2_Wrapper* boardGame2Logic;
        bool disposed;
    public:
        enum class PlayerTypeBoardGame2 {
            Human,
            Random,
            Ai
        };

        BoardGame2();
        ~BoardGame2();
        !BoardGame2();

        BoardGame2_Wrapper::PlayerType ConvertToNativePlayerType(PlayerTypeBoardGame2 playerType);
        void InitializeTheBoard_MC(String^ player1Name, String^ player2Name, 
                                 PlayerTypeBoardGame2 player1Type, PlayerTypeBoardGame2 player2Type);
        List<char>^ GetBoard_MC();
        int GetNumberOfMovesPlayed_MC();
        List<int>^ GetCurrentRowOfEachColumn_MC();
        String^ GetPlayer1Name_MC();
        String^ GetPlayer2Name_MC();
        KeyValuePair<int, int>^ GetPlayer1Move_MC();
        KeyValuePair<int, int>^ GetPlayer2Move_MC();
        void Player1PerformMove_MC(int x, int y);
        void Player2PerformMove_MC(int x, int y);
        bool IsValidMove_MC(int x, int y);
        bool isWin_MC();
        bool isDraw_MC();
        bool isGameOver_MC();
        void ClearGameState_MC();
    };

    // Game 3: 5x5 Tic-Tac-Toe
    public ref class BoardGame3 {
    private:
        FiveByFive_Board<char>* boardGame3Logic;
        bool disposed;
    public:
        enum class PlayerTypeBoardGame3 {
            Human,
            Random
        };

        BoardGame3();
        ~BoardGame3();
        !BoardGame3();

        void InitializeTheBoard_MC(String^ player1Name, String^ player2Name, 
                                 PlayerTypeBoardGame3 player1Type, PlayerTypeBoardGame3 player2Type);
        List<char>^ GetBoard_MC();
        int GetNumberOfMovesPlayed_MC();
        String^ GetPlayer1Name_MC();
        String^ GetPlayer2Name_MC();
        KeyValuePair<int, int>^ GetPlayer1Move_MC();
        KeyValuePair<int, int>^ GetPlayer2Move_MC();
        void Player1PerformMove_MC(int x, int y);
        void Player2PerformMove_MC(int x, int y);
        bool IsValidMove_MC(int x, int y);
        bool isWin_MC();
        bool isDraw_MC();
        bool isGameOver_MC();
        void ClearGameState_MC();
    };

    // Game 4: Word Tic-Tac-Toe
    public ref class BoardGame4 {
    private:
        Word_grid<char>* boardGame4Logic;
        bool disposed;
    public:
        enum class PlayerTypeBoardGame4 {
            Human,
            Random
        };

        BoardGame4();
        ~BoardGame4();
        !BoardGame4();

        void InitializeTheBoard_MC(String^ player1Name, String^ player2Name, 
                                 PlayerTypeBoardGame4 player1Type, PlayerTypeBoardGame4 player2Type);
        void SetFilename_MC(String^ filename);
        List<String^>^ GetBoard_MC();
        int GetNumberOfMovesPlayed_MC();
        String^ GetPlayer1Name_MC();
        String^ GetPlayer2Name_MC();
        KeyValuePair<int, int>^ GetPlayer1Move_MC();
        KeyValuePair<int, int>^ GetPlayer2Move_MC();
        void Player1PerformMove_MC(int x, int y, String^ word);
        void Player2PerformMove_MC(int x, int y, String^ word);
        bool ValidateWord_MC(String^ word);
        bool IsValidMove_MC(int x, int y);
        bool isWin_MC();
        bool isDraw_MC();
        bool isGameOver_MC();
        void ClearGameState_MC();
    };

    // Game 5: Numerical Tic-Tac-Toe
    public ref class BoardGame5 {
    private:
        BoardGame5_Wrapper* boardGame5Logic;
        bool disposed;
    public:
        enum class PlayerTypeBoardGame5 {
            Human,
            Random,
            Ai
        };

        BoardGame5();
        ~BoardGame5();
        !BoardGame5();

        BoardGame5_Wrapper::PlayerType ConvertToNativePlayerType(PlayerTypeBoardGame5 playerType);
        void InitializeTheBoard_MC(String^ player1Name, String^ player2Name, 
                                 PlayerTypeBoardGame5 player1Type, PlayerTypeBoardGame5 player2Type);
        List<int>^ GetBoard_MC();
        int GetNumberOfMovesPlayed_MC();
        String^ GetPlayer1Name_MC();
        String^ GetPlayer2Name_MC();
        List<int>^ GetPlayer1Move_MC();
        List<int>^ GetPlayer2Move_MC();
        List<int>^ GetAvailableNumbersForPlayer1_MC();
        List<int>^ GetAvailableNumbersForPlayer2_MC();
        void Player1PerformMove_MC(int x, int y);
        void Player2PerformMove_MC(int x, int y);
        bool IsValidMove_MC(int x, int y);
        bool isWin_MC();
        bool isDraw_MC();
        bool isGameOver_MC();
        void ClearGameState_MC();
    };

    // Game 6: Misere Tic-Tac-Toe (formerly Inverse)
    public ref class BoardGame6 {
    private:
        ThreeByThree_Board<char>* boardGame6Logic;
        bool disposed;
    public:
        enum class PlayerTypeBoardGame6 {
            Human,
            Random
        };

        BoardGame6();
        ~BoardGame6();
        !BoardGame6();

        void InitializeTheBoard_MC(String^ player1Name, String^ player2Name, 
                                 PlayerTypeBoardGame6 player1Type, PlayerTypeBoardGame6 player2Type);
        List<char>^ GetBoard_MC();
        int GetNumberOfMovesPlayed_MC();
        String^ GetPlayer1Name_MC();
        String^ GetPlayer2Name_MC();
        KeyValuePair<int, int>^ GetPlayer1Move_MC();
        KeyValuePair<int, int>^ GetPlayer2Move_MC();
        void Player1PerformMove_MC(int x, int y);
        void Player2PerformMove_MC(int x, int y);
        bool IsValidMove_MC(int x, int y);
        bool isWin_MC();
        bool isDraw_MC();
        bool isGameOver_MC();
        void ClearGameState_MC();
    };

    // Game 7: Four by Four Tic-Tac-Toe
    public ref class BoardGame7 {
    private:
        BoardGame7_Wrapper* boardGame7Logic;
        bool disposed;
    public:
        enum class PlayerTypeBoardGame7 {
            Human,
            Random
        };

        BoardGame7();
        ~BoardGame7();
        !BoardGame7();

        BoardGame7_Wrapper::PlayerType ConvertToNativePlayerType(PlayerTypeBoardGame7 playerType);
        void InitializeTheBoard_MC(String^ player1Name, String^ player2Name, 
                                 PlayerTypeBoardGame7 player1Type, PlayerTypeBoardGame7 player2Type);
        List<char>^ GetBoard_MC();
        int GetNumberOfMovesPlayed_MC();
        String^ GetPlayer1Name_MC();
        String^ GetPlayer2Name_MC();
        KeyValuePair<int, int>^ GetPlayer1Move_MC();
        KeyValuePair<int, int>^ GetPlayer2Move_MC();
        void SelectTokenForHumanPlayer_MC(int x, int y, int playerIndex);
        KeyValuePair<int, int>^ GetCurrentSelectedTokenPlayer1_MC();
        KeyValuePair<int, int>^ GetCurrentSelectedTokenPlayer2_MC();
        void Player1PerformMove_MC(int x, int y);
        void Player2PerformMove_MC(int x, int y);
        bool IsValidMove_MC(int x, int y);
        bool isWin_MC();
        bool isDraw_MC();
        bool isGameOver_MC();
        void ClearGameState_MC();
    };

    // Game 8: Ultimate Tic-Tac-Toe
    public ref class BoardGame8 {
    private:
        Ultimate_grid<char>* boardGame8Logic;
        bool disposed;
    public:
        enum class PlayerTypeBoardGame8 {
            Human,
            Random
        };

        BoardGame8();
        ~BoardGame8();
        !BoardGame8();

        void InitializeTheBoard_MC(String^ player1Name, String^ player2Name, 
                                 PlayerTypeBoardGame8 player1Type, PlayerTypeBoardGame8 player2Type);
        List<char>^ GetBoard_MC();
        List<char>^ GetBigBoard_MC();
        bool IsSubBoardComplete_MC(int boardIndex);
        int GetCurrentBoard_MC();
        void SetWin_MC(int position, char symbol);
        Dictionary<int, char>^ GetWinStatus_MC();
        int GetNumberOfMovesPlayed_MC();
        String^ GetPlayer1Name_MC();
        String^ GetPlayer2Name_MC();
        KeyValuePair<int, int>^ GetPlayer1Move_MC();
        KeyValuePair<int, int>^ GetPlayer2Move_MC();
        void Player1PerformMove_MC(int x, int y);
        void Player2PerformMove_MC(int x, int y);
        bool IsValidMove_MC(int x, int y);
        bool isWin_MC();
        bool isDraw_MC();
        bool isGameOver_MC();
        void ClearGameState_MC();
    };
}
   
