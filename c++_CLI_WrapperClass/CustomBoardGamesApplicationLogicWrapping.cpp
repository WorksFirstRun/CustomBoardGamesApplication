#include "pch.h"
#include "CustomBoardGamesApplicationLogicWrapping.h"


BoardGame2_Wrapper::PlayerType CustomBoardGamesApplicationLogicWrapping::BoardGame2::ConvertToNativePlayerType(
	PlayerTypeBoardGame2 playerType)
{
	switch (playerType)
	{
	case PlayerTypeBoardGame2::Human:
		return BoardGame2_Wrapper::PlayerType::Human;
	case PlayerTypeBoardGame2::RandomPlayer:
		return BoardGame2_Wrapper::PlayerType::Randomizer;
	case PlayerTypeBoardGame2::Ai:
		return BoardGame2_Wrapper::PlayerType::AI;
	default:
		throw gcnew ArgumentException("Invalid PlayerType");
	}
}

void CustomBoardGamesApplicationLogicWrapping::BoardGame2::InitializeTheBoard_MC(String^ player1Name, String^ player2Name,
                                                                              PlayerTypeBoardGame2 player1Type, PlayerTypeBoardGame2 player2Type)
{
    try
	{
	    string nativeString_Player1Name = msclr::interop::marshal_as<string>(player1Name);
	    string nativeString_Player2Name = msclr::interop::marshal_as<string>(player2Name);

	    boardGame2Logic->InitializeGame(nativeString_Player1Name, nativeString_Player1Name,
	        ConvertToNativePlayerType(player1Type), ConvertToNativePlayerType(player2Type));
	}
    catch (Exception^ ex)
    {
        Console::WriteLine("Error occurred in Initialization: " + ex->Message);
        throw;
    }
	
}

List<char>^ CustomBoardGamesApplicationLogicWrapping::BoardGame2::GetBoard_MC()
{
    List<char>^ boardList = gcnew List<char>();

    try
    {
        char** boardArray = boardGame2Logic->GetBoard();

        int rows = 6;
        int columns = 7;

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                boardList->Add(boardArray[i][j]);
            }
        }
    }
    catch (Exception^ ex)
    {
        Console::WriteLine("Error occurred in GetBoard_MC: " + ex->Message);
        throw;
    }

    return boardList;
}

int CustomBoardGamesApplicationLogicWrapping::BoardGame2::GetNumberOfMovesPlayed_MC()
{
    int n_moves = -1;
    try
    {
    	n_moves = boardGame2Logic->GetMovesPlayed();
    }
    catch (Exception ^ ex)
    {
        Console::WriteLine("Error occurred in GetNumberOfMovesPlayed_MC: " + ex->Message);
        throw;
    }
    return n_moves;
}

List<int> ^ CustomBoardGamesApplicationLogicWrapping::BoardGame2::GetCurrentRowOfEachColumn_MC()
{
    List<int>^ currentRows = gcnew List<int>();
    try
    {
        int* currentRowsArray = boardGame2Logic->GetCurrentRowOfEachColumn();

        for (int i = 0 ; i < 7 ; i++)
        {
            currentRows->Add(currentRowsArray[i]);
        }
    }
    catch(Exception ^ ex)
    {
        Console::WriteLine("Error occurred in GetCurrentRowOfEachColumn_MC: " + ex->Message);
        throw;
    }
    return currentRows;
}

String^ CustomBoardGamesApplicationLogicWrapping::BoardGame2::GetPlayer1Name_MC()
{
    String^ playerName = gcnew String("");
    try
    {
	    playerName = msclr::interop::marshal_as<String^>(boardGame2Logic->GetPlayer1Name());
    }
    catch(Exception ^ ex)
    {
        Console::WriteLine("Error occurred in GetPlayer1Name_MC: " + ex->Message);
        throw;
    }
	
    return playerName;
}

String^ CustomBoardGamesApplicationLogicWrapping::BoardGame2::GetPlayer2Name_MC()
{
    String^ playerName = gcnew String("");
    try
    {
        playerName = msclr::interop::marshal_as<String^>(boardGame2Logic->GetPlayer2Name());
    }
    catch (Exception^ ex)
    {
        Console::WriteLine("Error occurred in GetPlayer2Name_MC: " + ex->Message);
        throw;
    }

    return playerName;
}

KeyValuePair<int, int>^ CustomBoardGamesApplicationLogicWrapping::BoardGame2::GetPlayer1Move_MC()
{
   
    try
    {
        int x, y;
        boardGame2Logic->GetPlayer1Move(x, y);

        return gcnew KeyValuePair<int, int>(x, y);

    }
    catch (Exception ^ ex)
    {
        Console::WriteLine("Error occurred in GetPlayer1Move_MC: " + ex->Message);
        throw;
    }
}

KeyValuePair<int, int>^ CustomBoardGamesApplicationLogicWrapping::BoardGame2::GetPlayer2Move_MC()
{
    try
    {
        int x, y;
        boardGame2Logic->GetPlayer2Move(x, y);
        return gcnew KeyValuePair<int, int>(x, y);
    }
    catch (Exception^ ex)
    {
        Console::WriteLine("Error occurred in GetPlayer2Move_MC: " + ex->Message);
        throw;
    }
}

void CustomBoardGamesApplicationLogicWrapping::BoardGame2::Player1PerformMove_MC(int x, int y)
{
    try
    {
        boardGame2Logic->Player1PerformMove(x, y);
    }
    catch(Exception ^ ex)
    {
        Console::WriteLine("Error occurred in Player1PerformMove_MC: " + ex->Message);
        throw;
    }
}


void CustomBoardGamesApplicationLogicWrapping::BoardGame2::Player2PerformMove_MC(int x, int y)
{
    try
    {
        boardGame2Logic->Player2PerformMove(x, y);
    }
    catch (Exception^ ex)
    {
        Console::WriteLine("Error occurred in Player2PerformMove_MC: " + ex->Message);
        throw;
    }
}

bool CustomBoardGamesApplicationLogicWrapping::BoardGame2::isWin_MC()
{
    bool result = false;
    try
    {
        result = boardGame2Logic->isWin();
    }
    catch(Exception ^ ex)
    {
        Console::WriteLine("Error occurred in isWin_MC: " + ex->Message);
        throw;
    }
    return result;
}

bool CustomBoardGamesApplicationLogicWrapping::BoardGame2::isDraw_MC()
{
    bool result = false;
    try
    {
        result = boardGame2Logic->isDraw();
    }
    catch (Exception^ ex)
    {
        Console::WriteLine("Error occurred in isDraw_MC: " + ex->Message);
        throw;
    }
    return result;
}

bool CustomBoardGamesApplicationLogicWrapping::BoardGame2::isGameOver_MC()
{
    bool result = false;
    try
    {
        result = boardGame2Logic->isGameOver();
    }
    catch (Exception^ ex)
    {
        Console::WriteLine("Error occurred in isGameOver_MC: " + ex->Message);
        throw;
    }
    return result;
}

void CustomBoardGamesApplicationLogicWrapping::BoardGame2::ClearGameState_MC()
{
    try
    {
        boardGame2Logic->ClearGameState();
    }
    catch (Exception^ ex)
    {
        Console::WriteLine("Error occurred in ClearGameState_MC: " + ex->Message);
        throw;
    }
}

BoardGame5_Wrapper::PlayerType CustomBoardGamesApplicationLogicWrapping::BoardGame5::ConvertToNativePlayerType(
	PlayerTypeBoardGame5 playerType)
{
	switch (playerType)
	{
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

void CustomBoardGamesApplicationLogicWrapping::BoardGame5::InitializeTheBoard_MC(String^ player1Name,
	String^ player2Name, PlayerTypeBoardGame5 player1Type, PlayerTypeBoardGame5 player2Type)
{
	try
	{
		string nativeString_Player1Name = msclr::interop::marshal_as<string>(player1Name);
		string nativeString_Player2Name = msclr::interop::marshal_as<string>(player2Name);

		boardGame5Logic->InitializeGame(nativeString_Player1Name, nativeString_Player1Name,
			ConvertToNativePlayerType(player1Type), ConvertToNativePlayerType(player2Type));
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in Initialization: " + ex->Message);
		throw;
	}
}

List<int>^ CustomBoardGamesApplicationLogicWrapping::BoardGame5::GetBoard_MC()
{
	List<int>^ boardList = gcnew List<int>();

	try
	{
		int** boardArray = boardGame5Logic->GetBoard();

		int rows = 3;
		int columns = 3;

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				boardList->Add(boardArray[i][j]);
			}
		}
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetBoard_MC: " + ex->Message);
		throw;
	}

	return boardList;
}

int CustomBoardGamesApplicationLogicWrapping::BoardGame5::GetNumberOfMovesPlayed_MC()
{
	int n_moves = -1;
	try
	{
		n_moves = boardGame5Logic->GetMovesPlayed();
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetNumberOfMovesPlayed_MC: " + ex->Message);
		throw;
	}
	return n_moves;
}

String^ CustomBoardGamesApplicationLogicWrapping::BoardGame5::GetPlayer1Name_MC()
{
	String^ playerName = gcnew String("");
	try
	{
		playerName = msclr::interop::marshal_as<String^>(boardGame5Logic->GetPlayer1Name());
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetPlayer1Name_MC: " + ex->Message);
		throw;
	}

	return playerName;
}

String^ CustomBoardGamesApplicationLogicWrapping::BoardGame5::GetPlayer2Name_MC()
{
	String^ playerName = gcnew String("");
	try
	{
		playerName = msclr::interop::marshal_as<String^>(boardGame5Logic->GetPlayer2Name());
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetPlayer2Name_MC: " + ex->Message);
		throw;
	}

	return playerName;
}

List<int>^ CustomBoardGamesApplicationLogicWrapping::BoardGame5::GetPlayer1Move_MC()
{

	List<int>^ playerMoveResult = gcnew List<int>();
	try
	{
		int x, y, symbol;
		boardGame5Logic->GetPlayer1Move(x, y, symbol);
		playerMoveResult->Add(x);
		playerMoveResult->Add(y);
		playerMoveResult->Add(symbol);

	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetPlayer1Move_MC: " + ex->Message);
		throw;
	}
	return playerMoveResult;
}

List<int>^ CustomBoardGamesApplicationLogicWrapping::BoardGame5::GetPlayer2Move_MC()
{
	List<int>^ playerMoveResult = gcnew List<int>();
	try
	{
		int x, y, symbol;
		boardGame5Logic->GetPlayer2Move(x, y, symbol);
		playerMoveResult->Add(x);
		playerMoveResult->Add(y);
		playerMoveResult->Add(symbol);

	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetPlayer2Move_MC: " + ex->Message);
		throw;
	}
	return playerMoveResult;
}

List<int>^ CustomBoardGamesApplicationLogicWrapping::BoardGame5::GetAvailableNumbersForPlayer1_MC()
{
	List<int>^ playerAvailableNumbers = gcnew List<int>();
	try
	{
		vector<int> result = boardGame5Logic->GetAvailableNumbersForPlayer1();
		for (auto i : result)
		{
			playerAvailableNumbers->Add(i);
		}
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetAvailableNumbersForPlayer1_MC: " + ex->Message);
		throw;
	}
	return playerAvailableNumbers;
}

List<int>^ CustomBoardGamesApplicationLogicWrapping::BoardGame5::GetAvailableNumbersForPlayer2_MC()
{
	List<int>^ playerAvailableNumbers = gcnew List<int>();
	try
	{
		vector<int> result = boardGame5Logic->GetAvailableNumbersForPlayer2();
		for (auto i : result)
		{
			playerAvailableNumbers->Add(i);
		}
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetAvailableNumbersForPlayer2_MC: " + ex->Message);
		throw;
	}
	return playerAvailableNumbers;
}

void CustomBoardGamesApplicationLogicWrapping::BoardGame5::Player1PerformMove_MC(int x, int y)
{
	try
	{
		boardGame5Logic->Player1PerformMove(x, y);
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in Player1PerformMove_MC: " + ex->Message);
		throw;
	}
}

void CustomBoardGamesApplicationLogicWrapping::BoardGame5::Player2PerformMove_MC(int x, int y)
{
	try
	{
		boardGame5Logic->Player1PerformMove(x, y);
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in Player2PerformMove_MC: " + ex->Message);
		throw;
	}
}

bool CustomBoardGamesApplicationLogicWrapping::BoardGame5::isWin_MC()
{
	bool result = false;
	try
	{
		result = boardGame5Logic->isWin();
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in isWin_MC: " + ex->Message);
		throw;
	}
	return result;
}

bool CustomBoardGamesApplicationLogicWrapping::BoardGame5::isDraw_MC()
{
	bool result = false;
	try
	{
		result = boardGame5Logic->isWin();
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in isWin_MC: " + ex->Message);
		throw;
	}
	return result;
}

bool CustomBoardGamesApplicationLogicWrapping::BoardGame5::isGameOver_MC()
{
	bool result = false;
	try
	{
		result = boardGame5Logic->isGameOver();
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in isGameOver_MC: " + ex->Message);
		throw;
	}
	return result;
}

void CustomBoardGamesApplicationLogicWrapping::BoardGame5::ClearGameState_MC()
{
	try
	{
		boardGame5Logic->ClearGameState();
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in ClearGameState_MC: " + ex->Message);
		throw;
	}
}
















