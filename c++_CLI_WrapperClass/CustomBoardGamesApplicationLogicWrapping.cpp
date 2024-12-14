#include "pch.h"
#include "CustomBoardGamesApplicationLogicWrapping.h"
#include <msclr/marshal_cppstd.h>

using namespace System;
using namespace System::Collections::Generic;
using namespace msclr::interop;

namespace CustomBoardGamesApplicationLogicWrapping {

    private ref class GameException : public Exception {
    public:
        GameException(String^ message) : Exception(message) {}
    };

    // Validation helper
    void ValidateGameState(void* gameLogic) {
        if (gameLogic == nullptr) {
            throw gcnew GameException("Game not properly initialized");
        }
    }

    // Game 1: Pyramid Tic-Tac-Toe Implementation
    BoardGame1::BoardGame1() {
        boardGame1Logic = new Pyramid_grid<char>();
    }

    BoardGame1::~BoardGame1() {
        this->!BoardGame1();
    }

    BoardGame1::!BoardGame1() {
        ClearPlayers();
        delete boardGame1Logic;
    }

    void BoardGame1::ClearPlayers() {
        if (boardGame1Logic->players[0] != nullptr) {
            delete boardGame1Logic->players[0];
            boardGame1Logic->players[0] = nullptr;
        }
        if (boardGame1Logic->players[1] != nullptr) {
            delete boardGame1Logic->players[1];
            boardGame1Logic->players[1] = nullptr;
        }
    }

    Pyramid_grid<char>::PlayerType ConvertToNativePlayerType(PlayerTypeBoardGame1 playerType) {
        return (playerType == PlayerTypeBoardGame1::Human) ? 
            Pyramid_grid<char>::PlayerType::Human : 
            Pyramid_grid<char>::PlayerType::Random;
    }

    void BoardGame1::InitializeTheBoard_MC(String^ player1Name, String^ player2Name,
        PlayerTypeBoardGame1 player1Type, PlayerTypeBoardGame1 player2Type) 
    {
        try {
            string nativeString_Player1Name = msclr::interop::marshal_as<string>(player1Name);
            string nativeString_Player2Name = msclr::interop::marshal_as<string>(player2Name);

            Player<char>* player1;
            Player<char>* player2;

            if (player1Type == PlayerTypeBoardGame1::Human) {
                player1 = new Pyramid_Player<char>(nativeString_Player1Name, 'X');
            }
            else {
                player1 = new Pyramid_Random_Player<char>('X');
            }

            if (player2Type == PlayerTypeBoardGame1::Human) {
                player2 = new Pyramid_Player<char>(nativeString_Player2Name, 'O');
            }
            else {
                player2 = new Pyramid_Random_Player<char>('O');
            }

            boardGame1Logic->players[0] = player1;
            boardGame1Logic->players[1] = player2;
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    List<char>^ BoardGame1::GetBoard_MC() {
        List<char>^ boardList = gcnew List<char>();

        try {
            char** boardArray = boardGame1Logic->GetBoard();

            int rows = 5;
            int columns = 5;

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    boardList->Add(boardArray[i][j]);
                }
            }
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }

        return boardList;
    }

    int BoardGame1::GetNumberOfMovesPlayed_MC() {
        int n_moves = -1;
        try {
            n_moves = boardGame1Logic->GetMovesPlayed();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return n_moves;
    }

    String^ BoardGame1::GetPlayer1Name_MC() {
        String^ playerName = gcnew String("");
        try {
            playerName = msclr::interop::marshal_as<String^>(boardGame1Logic->GetPlayer1Name());
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }

        return playerName;
    }

    String^ BoardGame1::GetPlayer2Name_MC() {
        String^ playerName = gcnew String("");
        try {
            playerName = msclr::interop::marshal_as<String^>(boardGame1Logic->GetPlayer2Name());
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }

        return playerName;
    }

    KeyValuePair<int, int>^ BoardGame1::GetPlayer1Move_MC() {
        try {
            int x, y;
            boardGame1Logic->GetPlayer1Move(x, y);

            return gcnew KeyValuePair<int, int>(x, y);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    KeyValuePair<int, int>^ BoardGame1::GetPlayer2Move_MC() {
        try {
            int x, y;
            boardGame1Logic->GetPlayer2Move(x, y);

            return gcnew KeyValuePair<int, int>(x, y);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    void BoardGame1::Player1PerformMove_MC(int x, int y) {
        try {
            boardGame1Logic->Player1PerformMove(x, y);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    void BoardGame1::Player2PerformMove_MC(int x, int y) {
        try {
            boardGame1Logic->Player2PerformMove(x, y);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    bool BoardGame1::isWin_MC() {
        bool result = false;
        try {
            result = boardGame1Logic->isWin();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return result;
    }

    bool BoardGame1::isDraw_MC() {
        bool result = false;
        try {
            result = boardGame1Logic->isDraw();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return result;
    }

    bool BoardGame1::isGameOver_MC() {
        bool result = false;
        try {
            result = boardGame1Logic->isGameOver();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return result;
    }

    void BoardGame1::ClearGameState_MC() {
        try {
            boardGame1Logic->ClearGameState();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    // Game 2: Four in a Row (Already implemented)
    BoardGame2_Wrapper::PlayerType BoardGame2::ConvertToNativePlayerType(PlayerTypeBoardGame2 playerType) {
    try {
        switch (playerType) {
            case PlayerTypeBoardGame2::Human:
                return BoardGame2_Wrapper::PlayerType::Human;
            case PlayerTypeBoardGame2::RandomPlayer:
                return BoardGame2_Wrapper::PlayerType::Randomizer;
            case PlayerTypeBoardGame2::Ai:
                return BoardGame2_Wrapper::PlayerType::AI;
            default:
                throw gcnew GameException("Invalid player type");
        }
    }
    catch (Exception^ ex) {
        throw gcnew GameException("Error in player type conversion: " + ex->Message);
    }
}

// Add validation to InitializeTheBoard methods
void ValidatePlayerTypes(PlayerType player1Type, PlayerType player2Type) {
    if (!Enum::IsDefined(PlayerType::typeid, player1Type) ||
        !Enum::IsDefined(PlayerType::typeid, player2Type)) {
        throw gcnew GameException("Invalid player type specified");
    }
}

    void BoardGame2::InitializeTheBoard_MC(String^ player1Name, String^ player2Name,
        PlayerTypeBoardGame2 player1Type, PlayerTypeBoardGame2 player2Type) {
        try {
            string nativeString_Player1Name = msclr::interop::marshal_as<string>(player1Name);
            string nativeString_Player2Name = msclr::interop::marshal_as<string>(player2Name);

            ValidatePlayerTypes(player1Type, player2Type);

            boardGame2Logic->InitializeGame(nativeString_Player1Name, nativeString_Player2Name,
                ConvertToNativePlayerType(player1Type), ConvertToNativePlayerType(player2Type));
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    List<char>^ BoardGame2::GetBoard_MC() {
        List<char>^ boardList = gcnew List<char>();

        try {
            char** boardArray = boardGame2Logic->GetBoard();

            int rows = 6;
            int columns = 7;

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    boardList->Add(boardArray[i][j]);
                }
            }
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }

        return boardList;
    }

    int BoardGame2::GetNumberOfMovesPlayed_MC() {
        int n_moves = -1;
        try {
            n_moves = boardGame2Logic->GetMovesPlayed();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return n_moves;
    }

    List<int>^ BoardGame2::GetCurrentRowOfEachColumn_MC() {
        List<int>^ currentRows = gcnew List<int>();
        try {
            int* currentRowsArray = boardGame2Logic->GetCurrentRowOfEachColumn();

            for (int i = 0; i < 7; i++) {
                currentRows->Add(currentRowsArray[i]);
            }
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return currentRows;
    }

    String^ BoardGame2::GetPlayer1Name_MC() {
        String^ playerName = gcnew String("");
        try {
            playerName = msclr::interop::marshal_as<String^>(boardGame2Logic->GetPlayer1Name());
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return playerName;
    }

    String^ BoardGame2::GetPlayer2Name_MC() {
        String^ playerName = gcnew String("");
        try {
            playerName = msclr::interop::marshal_as<String^>(boardGame2Logic->GetPlayer2Name());
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }

        return playerName;
    }

    KeyValuePair<int, int>^ BoardGame2::GetPlayer1Move_MC() {
        try {
            int x, y;
            boardGame2Logic->GetPlayer1Move(x, y);

            return gcnew KeyValuePair<int, int>(x, y);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    KeyValuePair<int, int>^ BoardGame2::GetPlayer2Move_MC() {
        try {
            int x, y;
            boardGame2Logic->GetPlayer2Move(x, y);
            return gcnew KeyValuePair<int, int>(x, y);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    void BoardGame2::Player1PerformMove_MC(int x, int y) {
        try {
            boardGame2Logic->Player1PerformMove(x, y);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    void BoardGame2::Player2PerformMove_MC(int x, int y) {
        try {
            boardGame2Logic->Player2PerformMove(x, y);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    bool BoardGame2::isWin_MC() {
        bool result = false;
        try {
            result = boardGame2Logic->isWin();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return result;
    }

    bool BoardGame2::isDraw_MC() {
        bool result = false;
        try {
            result = boardGame2Logic->isDraw();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return result;
    }

    bool BoardGame2::isGameOver_MC() {
        bool result = false;
        try {
            result = boardGame2Logic->isGameOver();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return result;
    }

    void BoardGame2::ClearGameState_MC() {
        try {
            boardGame2Logic->ClearGameState();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    // Game 3: 5x5 Tic-Tac-Toe Implementation
    BoardGame3::BoardGame3() {
        boardGame3Logic = new FiveByFive_Board<char>();
    }

    BoardGame3::~BoardGame3() {
        this->!BoardGame3();
    }

    BoardGame3::!BoardGame3() {
        ClearPlayers();
        delete boardGame3Logic;
    }

    void BoardGame3::ClearPlayers() {
        if (boardGame3Logic->players[0] != nullptr) {
            delete boardGame3Logic->players[0];
            boardGame3Logic->players[0] = nullptr;
        }
        if (boardGame3Logic->players[1] != nullptr) {
            delete boardGame3Logic->players[1];
            boardGame3Logic->players[1] = nullptr;
        }
    }

    FiveByFive_Board<char>::PlayerType BoardGame3::ConvertToNativePlayerType(PlayerTypeBoardGame3 playerType) {
        return (playerType == PlayerTypeBoardGame3::Human) ? 
            FiveByFive_Board<char>::PlayerType::Human : 
            FiveByFive_Board<char>::PlayerType::Random;
    }

    void BoardGame3::InitializeTheBoard_MC(String^ player1Name, String^ player2Name,
        PlayerTypeBoardGame3 player1Type, PlayerTypeBoardGame3 player2Type) {
        try {
            string nativeString_Player1Name = msclr::interop::marshal_as<string>(player1Name);
            string nativeString_Player2Name = msclr::interop::marshal_as<string>(player2Name);

            Player<char>* player1;
            Player<char>* player2;

            if (player1Type == PlayerTypeBoardGame3::Human) {
                player1 = new FiveByFive_Player<char>(nativeString_Player1Name, 'X');
            }
            else {
                player1 = new FiveByFive_Random_Player<char>('X');
            }

            if (player2Type == PlayerTypeBoardGame3::Human) {
                player2 = new FiveByFive_Player<char>(nativeString_Player2Name, 'O');
            }
            else {
                player2 = new FiveByFive_Random_Player<char>('O');
            }

            boardGame3Logic->players[0] = player1;
            boardGame3Logic->players[1] = player2;
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    List<char>^ BoardGame3::GetBoard_MC() {
        List<char>^ boardList = gcnew List<char>();

        try {
            char** boardArray = boardGame3Logic->GetBoard();

            int rows = 5;
            int columns = 5;

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    boardList->Add(boardArray[i][j]);
                }
            }
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }

        return boardList;
    }

    int BoardGame3::GetNumberOfMovesPlayed_MC() {
        int n_moves = -1;
        try {
            n_moves = boardGame3Logic->GetMovesPlayed();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return n_moves;
    }

    String^ BoardGame3::GetPlayer1Name_MC() {
        String^ playerName = gcnew String("");
        try {
            playerName = msclr::interop::marshal_as<String^>(boardGame3Logic->GetPlayer1Name());
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }

        return playerName;
    }

    String^ BoardGame3::GetPlayer2Name_MC() {
        String^ playerName = gcnew String("");
        try {
            playerName = msclr::interop::marshal_as<String^>(boardGame3Logic->GetPlayer2Name());
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }

        return playerName;
    }

    KeyValuePair<int, int>^ BoardGame3::GetPlayer1Move_MC() {
        try {
            int x, y;
            boardGame3Logic->GetPlayer1Move(x, y);

            return gcnew KeyValuePair<int, int>(x, y);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    KeyValuePair<int, int>^ BoardGame3::GetPlayer2Move_MC() {
        try {
            int x, y;
            boardGame3Logic->GetPlayer2Move(x, y);

            return gcnew KeyValuePair<int, int>(x, y);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    void BoardGame3::Player1PerformMove_MC(int x, int y) {
        try {
            boardGame3Logic->Player1PerformMove(x, y);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    void BoardGame3::Player2PerformMove_MC(int x, int y) {
        try {
            boardGame3Logic->Player2PerformMove(x, y);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    bool BoardGame3::isWin_MC() {
        bool result = false;
        try {
            result = boardGame3Logic->isWin();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return result;
    }

    bool BoardGame3::isDraw_MC() {
        bool result = false;
        try {
            result = boardGame3Logic->isDraw();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return result;
    }

    bool BoardGame3::isGameOver_MC() {
        bool result = false;
        try {
            result = boardGame3Logic->isGameOver();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return result;
    }

    void BoardGame3::ClearGameState_MC() {
        try {
            boardGame3Logic->ClearGameState();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    bool BoardGame3::isPlayerTurnsFinished_MC() {
        bool result = false;
        try {
            result = boardGame3Logic->isPlayerTurnsFinished();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return result;
    }

    // Game 4: Word Tic-Tac-Toe Implementation
    BoardGame4::BoardGame4() {
        boardGame4Logic = new WordBoard<char>();
    }

    BoardGame4::~BoardGame4() {
        this->!BoardGame4();
    }

    BoardGame4::!BoardGame4() {
        ClearPlayers();
        delete boardGame4Logic;
    }

    void BoardGame4::ClearPlayers() {
        if (boardGame4Logic->players[0] != nullptr) {
            delete boardGame4Logic->players[0];
            boardGame4Logic->players[0] = nullptr;
        }
        if (boardGame4Logic->players[1] != nullptr) {
            delete boardGame4Logic->players[1];
            boardGame4Logic->players[1] = nullptr;
        }
    }

    WordBoard<char>::PlayerType BoardGame4::ConvertToNativePlayerType(PlayerTypeBoardGame4 playerType) {
        return (playerType == PlayerTypeBoardGame4::Human) ? 
            WordBoard<char>::PlayerType::Human : 
            WordBoard<char>::PlayerType::Random;
    }

    void BoardGame4::InitializeTheBoard_MC(String^ player1Name, String^ player2Name,
        PlayerTypeBoardGame4 player1Type, PlayerTypeBoardGame4 player2Type) {
        try {
            string nativeString_Player1Name = msclr::interop::marshal_as<string>(player1Name);
            string nativeString_Player2Name = msclr::interop::marshal_as<string>(player2Name);

            Player<char>* player1;
            Player<char>* player2;

            if (player1Type == PlayerTypeBoardGame4::Human) {
                player1 = new Word_Player<char>(nativeString_Player1Name, 'X');
            }
            else {
                player1 = new Word_Random_Player<char>('X');
            }

            if (player2Type == PlayerTypeBoardGame4::Human) {
                player2 = new Word_Player<char>(nativeString_Player2Name, 'O');
            }
            else {
                player2 = new Word_Random_Player<char>('O');
            }

            boardGame4Logic->players[0] = player1;
            boardGame4Logic->players[1] = player2;
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    List<char>^ BoardGame4::GetBoard_MC() {
        List<char>^ boardList = gcnew List<char>();

        try {
            char** boardArray = boardGame4Logic->GetBoard();

            int rows = 3;
            int columns = 3;

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    boardList->Add(boardArray[i][j]);
                }
            }
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }

        return boardList;
    }

    int BoardGame4::GetNumberOfMovesPlayed_MC() {
        int n_moves = -1;
        try {
            n_moves = boardGame4Logic->GetMovesPlayed();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return n_moves;
    }

    String^ BoardGame4::GetPlayer1Name_MC() {
        String^ playerName = gcnew String("");
        try {
            playerName = msclr::interop::marshal_as<String^>(boardGame4Logic->GetPlayer1Name());
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }

        return playerName;
    }

    String^ BoardGame4::GetPlayer2Name_MC() {
        String^ playerName = gcnew String("");
        try {
            playerName = msclr::interop::marshal_as<String^>(boardGame4Logic->GetPlayer2Name());
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }

        return playerName;
    }

    KeyValuePair<int, int>^ BoardGame4::GetPlayer1Move_MC() {
        try {
            int x, y;
            boardGame4Logic->GetPlayer1Move(x, y);

            return gcnew KeyValuePair<int, int>(x, y);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    KeyValuePair<int, int>^ BoardGame4::GetPlayer2Move_MC() {
        try {
            int x, y;
            boardGame4Logic->GetPlayer2Move(x, y);

            return gcnew KeyValuePair<int, int>(x, y);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    void BoardGame4::Player1PerformMove_MC(int x, int y) {
        try {
            boardGame4Logic->Player1PerformMove(x, y);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    void BoardGame4::Player2PerformMove_MC(int x, int y) {
        try {
            boardGame4Logic->Player2PerformMove(x, y);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    bool BoardGame4::isWin_MC() {
        bool result = false;
        try {
            result = boardGame4Logic->isWin();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return result;
    }

    bool BoardGame4::isDraw_MC() {
        bool result = false;
        try {
            result = boardGame4Logic->isDraw();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return result;
    }

    bool BoardGame4::isGameOver_MC() {
        bool result = false;
        try {
            result = boardGame4Logic->isGameOver();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return result;
    }

    void BoardGame4::ClearGameState_MC() {
        try {
            boardGame4Logic->ClearGameState();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    void BoardGame4::SetFilename_MC(String^ filename) {
        try {
            string nativeFilename = msclr::interop::marshal_as<string>(filename);
            boardGame4Logic->SetFilename(nativeFilename);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    bool BoardGame4::IsValid_MC(String^ word) {
        bool result = false;
        try {
            string nativeWord = msclr::interop::marshal_as<string>(word);
            result = boardGame4Logic->IsValid(nativeWord);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return result;
    }

    // Game 5: Numerical Tic-Tac-Toe (Already implemented)
    BoardGame5_Wrapper::PlayerType BoardGame5::ConvertToNativePlayerType(PlayerTypeBoardGame5 playerType) {
        switch (playerType) {
        case PlayerTypeBoardGame5::Human:
            return BoardGame5_Wrapper::PlayerType::Human;
        case PlayerTypeBoardGame5::Random:
            return BoardGame5_Wrapper::PlayerType::Randomizer;
        case PlayerTypeBoardGame5::Ai:
            return BoardGame5_Wrapper::PlayerType::AI;
        default:
            throw gcnew ArgumentException("Invalid PlayerType");
        }
    }

    void BoardGame5::InitializeTheBoard_MC(String^ player1Name, String^ player2Name,
        PlayerTypeBoardGame5 player1Type, PlayerTypeBoardGame5 player2Type) {
        try {
            string nativeString_Player1Name = msclr::interop::marshal_as<string>(player1Name);
            string nativeString_Player2Name = msclr::interop::marshal_as<string>(player2Name);

            boardGame5Logic->InitializeGame(nativeString_Player1Name, nativeString_Player2Name,
                ConvertToNativePlayerType(player1Type), ConvertToNativePlayerType(player2Type));
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    List<int>^ BoardGame5::GetBoard_MC() {
        List<int>^ boardList = gcnew List<int>();

        try {
            int** boardArray = boardGame5Logic->GetBoard();

            int rows = 3;
            int columns = 3;

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    boardList->Add(boardArray[i][j]);
                }
            }
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }

        return boardList;
    }

    int BoardGame5::GetNumberOfMovesPlayed_MC() {
        int n_moves = -1;
        try {
            n_moves = boardGame5Logic->GetMovesPlayed();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return n_moves;
    }

    String^ BoardGame5::GetPlayer1Name_MC() {
        String^ playerName = gcnew String("");
        try {
            playerName = msclr::interop::marshal_as<String^>(boardGame5Logic->GetPlayer1Name());
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }

        return playerName;
    }

    String^ BoardGame5::GetPlayer2Name_MC() {
        String^ playerName = gcnew String("");
        try {
            playerName = msclr::interop::marshal_as<String^>(boardGame5Logic->GetPlayer2Name());
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }

        return playerName;
    }

    List<int>^ BoardGame5::GetPlayer1Move_MC() {
        List<int>^ playerMoveResult = gcnew List<int>();
        try {
            int x, y, symbol;
            boardGame5Logic->GetPlayer1Move(x, y, symbol);
            playerMoveResult->Add(x);
            playerMoveResult->Add(y);
            playerMoveResult->Add(symbol);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return playerMoveResult;
    }

    List<int>^ BoardGame5::GetPlayer2Move_MC() {
        List<int>^ playerMoveResult = gcnew List<int>();
        try {
            int x, y, symbol;
            boardGame5Logic->GetPlayer2Move(x, y, symbol);
            playerMoveResult->Add(x);
            playerMoveResult->Add(y);
            playerMoveResult->Add(symbol);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return playerMoveResult;
    }

    List<int>^ BoardGame5::GetAvailableNumbersForPlayer1_MC() {
        List<int>^ playerAvailableNumbers = gcnew List<int>();
        try {
            vector<int> result = boardGame5Logic->GetAvailableNumbersForPlayer1();
            for (auto i : result) {
                playerAvailableNumbers->Add(i);
            }
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return playerAvailableNumbers;
    }

    List<int>^ BoardGame5::GetAvailableNumbersForPlayer2_MC() {
        List<int>^ playerAvailableNumbers = gcnew List<int>();
        try {
            vector<int> result = boardGame5Logic->GetAvailableNumbersForPlayer2();
            for (auto i : result) {
                playerAvailableNumbers->Add(i);
            }
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return playerAvailableNumbers;
    }

    void BoardGame5::Player1PerformMove_MC(int x, int y) {
        try {
            boardGame5Logic->Player1PerformMove(x, y);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    void BoardGame5::Player2PerformMove_MC(int x, int y) {
        try {
            boardGame5Logic->Player2PerformMove(x, y);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    bool BoardGame5::isWin_MC() {
        bool result = false;
        try {
            result = boardGame5Logic->isWin();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return result;
    }

    bool BoardGame5::isDraw_MC() {
        bool result = false;
        try {
            result = boardGame5Logic->isDraw();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return result;
    }

    bool BoardGame5::isGameOver_MC() {
        bool result = false;
        try {
            result = boardGame5Logic->isGameOver();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return result;
    }

    void BoardGame5::ClearGameState_MC() {
        try {
            boardGame5Logic->ClearGameState();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    // Game 6: Inverse Tic-Tac-Toe Implementation
    BoardGame6::BoardGame6() {
        boardGame6Logic = new ThreeByThree_Board<char>();
    }

    BoardGame6::~BoardGame6() {
        this->!BoardGame6();
    }

    BoardGame6::!BoardGame6() {
        ClearPlayers();
        delete boardGame6Logic;
    }

    void BoardGame6::ClearPlayers() {
        if (boardGame6Logic->players[0] != nullptr) {
            delete boardGame6Logic->players[0];
            boardGame6Logic->players[0] = nullptr;
        }
        if (boardGame6Logic->players[1] != nullptr) {
            delete boardGame6Logic->players[1];
            boardGame6Logic->players[1] = nullptr;
        }
    }

    ThreeByThree_Board<char>::PlayerType BoardGame6::ConvertToNativePlayerType(PlayerTypeBoardGame6 playerType) {
        return (playerType == PlayerTypeBoardGame6::Human) ? 
            ThreeByThree_Board<char>::PlayerType::Human : 
            ThreeByThree_Board<char>::PlayerType::Random;
    }

    void BoardGame6::InitializeTheBoard_MC(String^ player1Name, String^ player2Name,
        PlayerTypeBoardGame6 player1Type, PlayerTypeBoardGame6 player2Type) {
        try {
            string nativeString_Player1Name = msclr::interop::marshal_as<string>(player1Name);
            string nativeString_Player2Name = msclr::interop::marshal_as<string>(player2Name);

            Player<char>* player1;
            Player<char>* player2;

            if (player1Type == PlayerTypeBoardGame6::Human) {
                player1 = new ThreeByThree_Player<char>(nativeString_Player1Name, 'X');
            }
            else {
                player1 = new ThreeByThree_Random_Player<char>('X');
            }

            if (player2Type == PlayerTypeBoardGame6::Human) {
                player2 = new ThreeByThree_Player<char>(nativeString_Player2Name, 'O');
            }
            else {
                player2 = new ThreeByThree_Random_Player<char>('O');
            }

            boardGame6Logic->players[0] = player1;
            boardGame6Logic->players[1] = player2;
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    List<char>^ BoardGame6::GetBoard_MC() {
        List<char>^ boardList = gcnew List<char>();

        try {
            char** boardArray = boardGame6Logic->GetBoard();

            int rows = 3;
            int columns = 3;

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    boardList->Add(boardArray[i][j]);
                }
            }
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }

        return boardList;
    }

    int BoardGame6::GetNumberOfMovesPlayed_MC() {
        int n_moves = -1;
        try {
            n_moves = boardGame6Logic->GetMovesPlayed();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return n_moves;
    }

    String^ BoardGame6::GetPlayer1Name_MC() {
        String^ playerName = gcnew String("");
        try {
            playerName = msclr::interop::marshal_as<String^>(boardGame6Logic->GetPlayer1Name());
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }

        return playerName;
    }

    String^ BoardGame6::GetPlayer2Name_MC() {
        String^ playerName = gcnew String("");
        try {
            playerName = msclr::interop::marshal_as<String^>(boardGame6Logic->GetPlayer2Name());
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }

        return playerName;
    }

    KeyValuePair<int, int>^ BoardGame6::GetPlayer1Move_MC() {
        try {
            int x, y;
            boardGame6Logic->GetPlayer1Move(x, y);

            return gcnew KeyValuePair<int, int>(x, y);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    KeyValuePair<int, int>^ BoardGame6::GetPlayer2Move_MC() {
        try {
            int x, y;
            boardGame6Logic->GetPlayer2Move(x, y);

            return gcnew KeyValuePair<int, int>(x, y);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    void BoardGame6::Player1PerformMove_MC(int x, int y) {
        try {
            boardGame6Logic->Player1PerformMove(x, y);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    void BoardGame6::Player2PerformMove_MC(int x, int y) {
        try {
            boardGame6Logic->Player2PerformMove(x, y);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    bool BoardGame6::isWin_MC() {
        bool result = false;
        try {
            result = boardGame6Logic->isWin();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return result;
    }

    bool BoardGame6::isDraw_MC() {
        bool result = false;
        try {
            result = boardGame6Logic->isDraw();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return result;
    }

    bool BoardGame6::isGameOver_MC() {
        bool result = false;
        try {
            result = boardGame6Logic->isGameOver();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return result;
    }

    void BoardGame6::ClearGameState_MC() {
        try {
            boardGame6Logic->ClearGameState();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    bool BoardGame6::IsThere_a_Winner_MC() {
        bool result = false;
        try {
            result = boardGame6Logic->IsThere_a_Winner();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return result;
    }

    // Game 7: Four by Four Tic-Tac-Toe (Already implemented)
    BoardGame7_Wrapper::PlayerType BoardGame7::ConvertToNativePlayerType(PlayerTypeBoardGame7 playerType) {
        return (playerType == PlayerTypeBoardGame7::Human) ? 
            BoardGame7_Wrapper::PlayerType::Human : 
            BoardGame7_Wrapper::PlayerType::Random;
    }

    void BoardGame7::InitializeTheBoard_MC(String^ player1Name, String^ player2Name,
        PlayerTypeBoardGame7 player1Type, PlayerTypeBoardGame7 player2Type) {
        try {
            string nativeString_Player1Name = msclr::interop::marshal_as<string>(player1Name);
            string nativeString_Player2Name = msclr::interop::marshal_as<string>(player2Name);

            boardGame7Logic->InitializeGame(nativeString_Player1Name, nativeString_Player2Name,
                ConvertToNativePlayerType(player1Type), ConvertToNativePlayerType(player2Type));
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    List<List<char>^>^ BoardGame7::GetBoard_MC() {
        List<List<char>^>^ boardList = gcnew List<List<char>^>();

        try {
            vector<vector<char>> boardArray = boardGame7Logic->GetBoard();

            for (int i = 0; i < boardArray.size(); i++) {
                List<char>^ innerList = gcnew List<char>();
                for (auto V : boardArray[i]) {
                    innerList->Add(V);
                }
                boardList->Add(innerList);
            }
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }

        return boardList;
    }

    int BoardGame7::GetNumberOfMovesPlayed_MC() {
        int n_moves = -1;
        try {
            n_moves = boardGame7Logic->GetMovesPlayed();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return n_moves;
    }

    String^ BoardGame7::GetPlayer1Name_MC() {
        String^ playerName = gcnew String("");
        try {
            playerName = msclr::interop::marshal_as<String^>(boardGame7Logic->GetPlayer1Name());
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }

        return playerName;
    }

    String^ BoardGame7::GetPlayer2Name_MC() {
        String^ playerName = gcnew String("");
        try {
            playerName = msclr::interop::marshal_as<String^>(boardGame7Logic->GetPlayer2Name());
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }

        return playerName;
    }

    KeyValuePair<int, int>^ BoardGame7::GetPlayer1Move_MC() {
        try {
            int x, y;
            boardGame7Logic->GetPlayer1Move(x, y);

            return gcnew KeyValuePair<int, int>(x, y);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    KeyValuePair<int, int>^ BoardGame7::GetPlayer2Move_MC() {
        try {
            int x, y;
            boardGame7Logic->GetPlayer2Move(x, y);

            return gcnew KeyValuePair<int, int>(x, y);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    void BoardGame7::SelectTokenForHumanPlayer_MC(int x, int y, int playerIndex) {
        try {
            boardGame7Logic->SelectTokenForHumanPlayer(x, y, playerIndex);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    KeyValuePair<int, int>^ BoardGame7::GetCurrentSelectedTokenPlayer1_MC() {
        try {
            int x, y;
            pair<int, int> currentToken = boardGame7Logic->GetCurrentSelectedTokenPlayer1();

            x = currentToken.first;
            y = currentToken.second;

            return gcnew KeyValuePair<int, int>(x, y);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    KeyValuePair<int, int>^ BoardGame7::GetCurrentSelectedTokenPlayer2_MC() {
        try {
            int x, y;
            pair<int, int> currentToken = boardGame7Logic->GetCurrentSelectedTokenPlayer2();

            x = currentToken.first;
            y = currentToken.second;

            return gcnew KeyValuePair<int, int>(x, y);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    void BoardGame7::Player1PerformMove_MC(int x, int y) {
        try {
            boardGame7Logic->Player1PerformMove(x, y);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    void BoardGame7::Player2PerformMove_MC(int x, int y) {
        try {
            boardGame7Logic->Player2PerformMove(x, y);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    bool BoardGame7::isWin_MC() {
        bool result = false;
        try {
            result = boardGame7Logic->isWin();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return result;
    }

    bool BoardGame7::isDraw_MC() {
        bool result = false;
        try {
            result = boardGame7Logic->isDraw();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return result;
    }

    bool BoardGame7::isGameOver_MC() {
        bool result = false;
        try {
            result = boardGame7Logic->isGameOver();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return result;
    }

    void BoardGame7::ClearGameState_MC() {
        try {
            boardGame7Logic->ClearGameState();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    // Game 8: Ultimate Tic-Tac-Toe Implementation
    BoardGame8::BoardGame8() {
        boardGame8Logic = new Ultimate_grid<char>();
    }

    BoardGame8::~BoardGame8() {
        this->!BoardGame8();
    }

    BoardGame8::!BoardGame8() {
        ClearPlayers();
        delete boardGame8Logic;
    }

    void BoardGame8::ClearPlayers() {
        if (boardGame8Logic->players[0] != nullptr) {
            delete boardGame8Logic->players[0];
            boardGame8Logic->players[0] = nullptr;
        }
        if (boardGame8Logic->players[1] != nullptr) {
            delete boardGame8Logic->players[1];
            boardGame8Logic->players[1] = nullptr;
        }
    }

    Ultimate_grid<char>::PlayerType BoardGame8::ConvertToNativePlayerType(PlayerTypeBoardGame8 playerType) {
        return (playerType == PlayerTypeBoardGame8::Human) ? 
            Ultimate_grid<char>::PlayerType::Human : 
            Ultimate_grid<char>::PlayerType::Random;
    }

    void BoardGame8::InitializeTheBoard_MC(String^ player1Name, String^ player2Name,
        PlayerTypeBoardGame8 player1Type, PlayerTypeBoardGame8 player2Type) {
        try {
            string nativeString_Player1Name = msclr::interop::marshal_as<string>(player1Name);
            string nativeString_Player2Name = msclr::interop::marshal_as<string>(player2Name);

            Player<char>* player1;
            Player<char>* player2;

            if (player1Type == PlayerTypeBoardGame8::Human) {
                player1 = new Ultimate_Player<char>(nativeString_Player1Name, 'X');
            }
            else {
                player1 = new Ultimate_Random_Player<char>('X');
            }

            if (player2Type == PlayerTypeBoardGame8::Human) {
                player2 = new Ultimate_Player<char>(nativeString_Player2Name, 'O');
            }
            else {
                player2 = new Ultimate_Random_Player<char>('O');
            }

            boardGame8Logic->players[0] = player1;
            boardGame8Logic->players[1] = player2;
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    List<List<char>^>^ BoardGame8::GetBoard_MC() {
        List<List<char>^>^ boardList = gcnew List<List<char>^>();

        try {
            vector<vector<char>> boardArray = boardGame8Logic->GetBoard();

            for (int i = 0; i < boardArray.size(); i++) {
                List<char>^ innerList = gcnew List<char>();
                for (auto V : boardArray[i]) {
                    innerList->Add(V);
                }
                boardList->Add(innerList);
            }
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }

        return boardList;
    }

    int BoardGame8::GetNumberOfMovesPlayed_MC() {
        int n_moves = -1;
        try {
            n_moves = boardGame8Logic->GetMovesPlayed();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return n_moves;
    }

    String^ BoardGame8::GetPlayer1Name_MC() {
        String^ playerName = gcnew String("");
        try {
            playerName = msclr::interop::marshal_as<String^>(boardGame8Logic->GetPlayer1Name());
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }

        return playerName;
    }

    String^ BoardGame8::GetPlayer2Name_MC() {
        String^ playerName = gcnew String("");
        try {
            playerName = msclr::interop::marshal_as<String^>(boardGame8Logic->GetPlayer2Name());
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }

        return playerName;
    }

    KeyValuePair<int, int>^ BoardGame8::GetPlayer1Move_MC() {
        try {
            int x, y;
            boardGame8Logic->GetPlayer1Move(x, y);

            return gcnew KeyValuePair<int, int>(x, y);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    KeyValuePair<int, int>^ BoardGame8::GetPlayer2Move_MC() {
        try {
            int x, y;
            boardGame8Logic->GetPlayer2Move(x, y);

            return gcnew KeyValuePair<int, int>(x, y);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    void BoardGame8::Player1PerformMove_MC(int x, int y) {
        try {
            boardGame8Logic->Player1PerformMove(x, y);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    void BoardGame8::Player2PerformMove_MC(int x, int y) {
        try {
            boardGame8Logic->Player2PerformMove(x, y);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    bool BoardGame8::isWin_MC() {
        bool result = false;
        try {
            result = boardGame8Logic->isWin();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return result;
    }

    bool BoardGame8::isDraw_MC() {
        bool result = false;
        try {
            result = boardGame8Logic->isDraw();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return result;
    }

    bool BoardGame8::isGameOver_MC() {
        bool result = false;
        try {
            result = boardGame8Logic->isGameOver();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return result;
    }

    void BoardGame8::ClearGameState_MC() {
        try {
            boardGame8Logic->ClearGameState();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    void BoardGame8::SetWin_MC(int x, int y) {
        try {
            boardGame8Logic->SetWin(x, y);
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
    }

    int BoardGame8::GetWinStatus_MC() {
        int result = -1;
        try {
            result = boardGame8Logic->GetWinStatus();
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }
        return result;
    }

    List<List<char>^>^ BoardGame8::GetBigBoard_MC() {
        List<List<char>^>^ boardList = gcnew List<List<char>^>();

        try {
            vector<vector<char>> boardArray = boardGame8Logic->GetBigBoard();

            for (int i = 0; i < boardArray.size(); i++) {
                List<char>^ innerList = gcnew List<char>();
                for (auto V : boardArray[i]) {
                    innerList->Add(V);
                }
                boardList->Add(innerList);
            }
        }
        catch (const std::exception& e) {
            String^ errorMessage = gcnew String(e.what());
            throw gcnew GameException("Native error: " + errorMessage);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Managed error: " + ex->Message);
        }

        return boardList;
    }

    bool BoardGame1::IsValidMove_MC(int x, int y) {
        try {
            return boardGame1Logic->is_valid_move(x, y);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Error validating move: " + ex->Message);
        }
    }

    void BoardGame2::ValidateGameState() {
        if (boardGame2Logic == nullptr) {
            throw gcnew GameException("Game not properly initialized");
        }
    }

    bool BoardGame3::IsValidMove_MC(int x, int y) {
        try {
            return boardGame3Logic->is_valid_move(x, y);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Error validating move: " + ex->Message);
        }
    }

    void BoardGame3::ValidateGameState() {
        if (boardGame3Logic == nullptr) {
            throw gcnew GameException("Game not properly initialized");
        }
    }

    bool BoardGame4::IsValidMove_MC(int x, int y) {
        try {
            return boardGame4Logic->is_valid_move(x, y);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Error validating move: " + ex->Message);
        }
    }

    void BoardGame4::ValidateGameState() {
        if (boardGame4Logic == nullptr) {
            throw gcnew GameException("Game not properly initialized");
        }
    }

    bool BoardGame5::IsValidMove_MC(int x, int y) {
        try {
            return boardGame5Logic->is_valid_move(x, y);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Error validating move: " + ex->Message);
        }
    }

    void BoardGame5::ValidateGameState() {
        if (boardGame5Logic == nullptr) {
            throw gcnew GameException("Game not properly initialized");
        }
    }

    bool BoardGame6::IsValidMove_MC(int x, int y) {
        try {
            return boardGame6Logic->is_valid_move(x, y);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Error validating move: " + ex->Message);
        }
    }

    void BoardGame6::ValidateGameState() {
        if (boardGame6Logic == nullptr) {
            throw gcnew GameException("Game not properly initialized");
        }
    }

    bool BoardGame7::IsValidMove_MC(int x, int y) {
        try {
            return boardGame7Logic->is_valid_move(x, y);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Error validating move: " + ex->Message);
        }
    }

    void BoardGame7::ValidateGameState() {
        if (boardGame7Logic == nullptr) {
            throw gcnew GameException("Game not properly initialized");
        }
    }

    bool BoardGame8::IsValidMove_MC(int x, int y) {
        try {
            return boardGame8Logic->is_valid_move(x, y);
        }
        catch (Exception^ ex) {
            throw gcnew GameException("Error validating move: " + ex->Message);
        }
    }

    void BoardGame8::ValidateGameState() {
        if (boardGame8Logic == nullptr) {
            throw gcnew GameException("Game not properly initialized");
        }
    }

    bool disposed = false;

    protected:
        void Dispose(bool disposing) {
            if (!disposed) {
                if (disposing) {
                    this->!BoardGameX();
                }
                disposed = true;
            }
        }

    public:
        void Dispose() {
            Dispose(true);
            GC::SuppressFinalize(this);
        }
}

