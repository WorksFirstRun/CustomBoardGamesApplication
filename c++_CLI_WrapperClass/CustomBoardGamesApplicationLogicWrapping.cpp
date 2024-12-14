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

	    boardGame2Logic->InitializeGame(nativeString_Player1Name, nativeString_Player2Name,
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

		boardGame5Logic->InitializeGame(nativeString_Player1Name, nativeString_Player2Name,
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
		boardGame5Logic->Player2PerformMove(x, y);
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
		result = boardGame5Logic->isDraw();
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in isDraw_MC: " + ex->Message);
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

BoardGame7_Wrapper::PlayerType CustomBoardGamesApplicationLogicWrapping::BoardGame7::ConvertToNativePlayerType(
	PlayerTypeBoardGame7 playerType)
{
	switch (playerType)
	{
	case PlayerTypeBoardGame7::Human:
		return BoardGame7_Wrapper::PlayerType::Human;
	case PlayerTypeBoardGame7::Random:
		return BoardGame7_Wrapper::PlayerType::Randomizer;
	default:
		throw gcnew ArgumentException("Invalid PlayerType");
	}
}

void CustomBoardGamesApplicationLogicWrapping::BoardGame7::InitializeTheBoard_MC(String^ player1Name,
	String^ player2Name, PlayerTypeBoardGame7 player1Type, PlayerTypeBoardGame7 player2Type)
{
	try
	{
		string nativeString_Player1Name = msclr::interop::marshal_as<string>(player1Name);
		string nativeString_Player2Name = msclr::interop::marshal_as<string>(player2Name);

		boardGame7Logic->InitializeGame(nativeString_Player1Name, nativeString_Player2Name,
			ConvertToNativePlayerType(player1Type), ConvertToNativePlayerType(player2Type));
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in Initialization: " + ex->Message);
		throw;
	}
}

List<List<char> ^>^ CustomBoardGamesApplicationLogicWrapping::BoardGame7::GetBoard_MC()
{
	List<List<char> ^>^ boardList = gcnew List<List<char> ^>();

	try
	{
		vector<vector<char>> boardArray = boardGame7Logic->GetBoard();

		for (int i = 0; i < boardArray.size(); i++)
		{
			List<char>^ innerList = gcnew List<char>();
			for (auto V : boardArray[i])
			{
				innerList->Add(V);
			}
			boardList->Add(innerList); 
		}
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetBoard_MC: " + ex->Message);
		throw;
	}

	return boardList;
}

int CustomBoardGamesApplicationLogicWrapping::BoardGame7::GetNumberOfMovesPlayed_MC()
{
	int n_moves = -1;
	try
	{
		n_moves = boardGame7Logic->GetMovesPlayed();
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetNumberOfMovesPlayed_MC: " + ex->Message);
		throw;
	}
	return n_moves;
}

String^ CustomBoardGamesApplicationLogicWrapping::BoardGame7::GetPlayer1Name_MC()
{
	String^ playerName = gcnew String("");
	try
	{
		playerName = msclr::interop::marshal_as<String^>(boardGame7Logic->GetPlayer1Name());
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetPlayer1Name_MC: " + ex->Message);
		throw;
	}

	return playerName;
}

String^ CustomBoardGamesApplicationLogicWrapping::BoardGame7::GetPlayer2Name_MC()
{
	String^ playerName = gcnew String("");
	try
	{
		playerName = msclr::interop::marshal_as<String^>(boardGame7Logic->GetPlayer2Name());
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetPlayer2Name_MC: " + ex->Message);
		throw;
	}

	return playerName;
}

KeyValuePair<int, int>^ CustomBoardGamesApplicationLogicWrapping::BoardGame7::GetPlayer1Move_MC()
{
	try
	{
		int x, y;
		boardGame7Logic->GetPlayer1Move(x, y);

		return gcnew KeyValuePair<int, int>(x, y);
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetPlayer1Move_MC: " + ex->Message);
		throw;
	}
}

KeyValuePair<int, int>^ CustomBoardGamesApplicationLogicWrapping::BoardGame7::GetPlayer2Move_MC()
{
	try
	{
		int x, y;
		boardGame7Logic->GetPlayer2Move(x, y);

		return gcnew KeyValuePair<int, int>(x, y);

	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetPlayer2Move_MC: " + ex->Message);
		throw;
	}
}

void CustomBoardGamesApplicationLogicWrapping::BoardGame7::SelectTokenForHumanPlayer_MC(int x, int y, int playerIndex)
{
	try
	{
		boardGame7Logic->SelectTokenForHumanPlayer(x, y, playerIndex);
	}
	catch(Exception ^ ex)
	{
		Console::WriteLine("Error occurred in SelectTokenForHumanPlayer_MC: " + ex->Message);
		throw;
	}
}

KeyValuePair<int, int>^ CustomBoardGamesApplicationLogicWrapping::BoardGame7::GetCurrentSelectedTokenPlayer1_MC()
{
	try
	{
		int x, y;
		pair<int, int> currentToken = boardGame7Logic->GetCurrentSelectedTokenPlayer1();

		x = currentToken.first;
		y = currentToken.second;

		return gcnew KeyValuePair<int, int>(x, y);

	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetCurrentSelectedTokenPlayer1_MC: " + ex->Message);
		throw;
	}
}

KeyValuePair<int, int>^ CustomBoardGamesApplicationLogicWrapping::BoardGame7::GetCurrentSelectedTokenPlayer2_MC()
{
	try
	{
		int x, y;
		pair<int, int> currentToken = boardGame7Logic->GetCurrentSelectedTokenPlayer2();

		x = currentToken.first;
		y = currentToken.second;

		return gcnew KeyValuePair<int, int>(x, y);

	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetCurrentSelectedTokenPlayer2_MC: " + ex->Message);
		throw;
	}
}

void CustomBoardGamesApplicationLogicWrapping::BoardGame7::Player1PerformMove_MC(int x, int y)
{
	try
	{
		boardGame7Logic->Player1PerformMove(x, y);
	}
	catch(Exception ^ ex)
	{
		Console::WriteLine("Error occurred in Player1PerformMove_MC: " + ex->Message);
		throw;
	}
}


void CustomBoardGamesApplicationLogicWrapping::BoardGame7::Player2PerformMove_MC(int x, int y)
{
	try
	{
		boardGame7Logic->Player2PerformMove(x, y);
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in Player2PerformMove_MC: " + ex->Message);
		throw;
	}
}

bool CustomBoardGamesApplicationLogicWrapping::BoardGame7::isWin_MC()
{
	bool result = false;
	try
	{
		result = boardGame7Logic->isWin();
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in isWin_MC: " + ex->Message);
		throw;
	}
	return result;
}

bool CustomBoardGamesApplicationLogicWrapping::BoardGame7::isDraw_MC()
{
	bool result = false;
	try
	{
		result = boardGame7Logic->isDraw();
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in isDraw_MC: " + ex->Message);
		throw;
	}
	return result;
}

bool CustomBoardGamesApplicationLogicWrapping::BoardGame7::isGameOver_MC()
{
	bool result = false;
	try
	{
		result = boardGame7Logic->isGameOver();
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in isGameOver_MC: " + ex->Message);
		throw;
	}
	return result;
}

void CustomBoardGamesApplicationLogicWrapping::BoardGame7::ClearGameState_MC()
{
	try
	{
		boardGame7Logic->ClearGameState();
	}
	catch(Exception ^ ex)
	{
		Console::WriteLine("Error occurred in ClearGameState_MC: " + ex->Message);
		throw;
	}
}

BoardGame1_Wrapper::PlayerType CustomBoardGamesApplicationLogicWrapping::BoardGame1::ConvertToNativePlayerType(
	PlayerTypeBoardGame1 playerType)
{
	switch (playerType)
	{
	case PlayerTypeBoardGame1::Human:
		return BoardGame1_Wrapper::PlayerType::Human;
	case PlayerTypeBoardGame1::Random:
		return BoardGame1_Wrapper::PlayerType::Randomizer;
	default:
		throw gcnew ArgumentException("Invalid PlayerType");
	}
}

void CustomBoardGamesApplicationLogicWrapping::BoardGame1::InitializeTheBoard_MC(String^ player1Name,
	String^ player2Name, PlayerTypeBoardGame1 player1Type, PlayerTypeBoardGame1 player2Type)
{
	try
	{
		string nativeString_Player1Name = msclr::interop::marshal_as<string>(player1Name);
		string nativeString_Player2Name = msclr::interop::marshal_as<string>(player2Name);

		boardGame1Logic->InitializeGame(nativeString_Player1Name, nativeString_Player2Name,
			ConvertToNativePlayerType(player1Type), ConvertToNativePlayerType(player2Type));
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in Initialization: " + ex->Message);
		throw;
	}
}

List<char>^ CustomBoardGamesApplicationLogicWrapping::BoardGame1::GetBoard_MC()
{
	List<char>^ boardList = gcnew List<char>();

	try
	{
		char** boardArray = boardGame1Logic->GetBoard();
		int size = boardGame1Logic->GetBoardSize();

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
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

int CustomBoardGamesApplicationLogicWrapping::BoardGame1::GetNumberOfMovesPlayed_MC()
{
	int n_moves = -1;
	try
	{
		n_moves = boardGame1Logic->GetMovesPlayed();
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetNumberOfMovesPlayed_MC: " + ex->Message);
		throw;
	}
	return n_moves;
}

String^ CustomBoardGamesApplicationLogicWrapping::BoardGame1::GetPlayer1Name_MC()
{
	String^ playerName = gcnew String("");
	try
	{
		playerName = msclr::interop::marshal_as<String^>(boardGame1Logic->GetPlayer1Name());
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetPlayer1Name_MC: " + ex->Message);
		throw;
	}

	return playerName;
}

String^ CustomBoardGamesApplicationLogicWrapping::BoardGame1::GetPlayer2Name_MC()
{
	String^ playerName = gcnew String("");
	try
	{
		playerName = msclr::interop::marshal_as<String^>(boardGame1Logic->GetPlayer2Name());
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetPlayer2Name_MC: " + ex->Message);
		throw;
	}

	return playerName;
}

KeyValuePair<int, int>^ CustomBoardGamesApplicationLogicWrapping::BoardGame1::GetPlayer1Move_MC()
{
	try
	{
		int x, y;
		boardGame1Logic->GetPlayer1Move(x, y);
		return gcnew KeyValuePair<int, int>(x, y);
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetPlayer1Move_MC: " + ex->Message);
		throw;
	}
}

KeyValuePair<int, int>^ CustomBoardGamesApplicationLogicWrapping::BoardGame1::GetPlayer2Move_MC()
{
	try
	{
		int x, y;
		boardGame1Logic->GetPlayer2Move(x, y);
		return gcnew KeyValuePair<int, int>(x, y);
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetPlayer2Move_MC: " + ex->Message);
		throw;
	}
}

void CustomBoardGamesApplicationLogicWrapping::BoardGame1::Player1PerformMove_MC(int x, int y)
{
	try
	{
		boardGame1Logic->Player1PerformMove(x, y);
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in Player1PerformMove_MC: " + ex->Message);
		throw;
	}
}

void CustomBoardGamesApplicationLogicWrapping::BoardGame1::Player2PerformMove_MC(int x, int y)
{
	try
	{
		boardGame1Logic->Player2PerformMove(x, y);
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in Player2PerformMove_MC: " + ex->Message);
		throw;
	}
}

bool CustomBoardGamesApplicationLogicWrapping::BoardGame1::isWin_MC()
{
	bool result = false;
	try
	{
		result = boardGame1Logic->isWin();
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in isWin_MC: " + ex->Message);
		throw;
	}
	return result;
}

bool CustomBoardGamesApplicationLogicWrapping::BoardGame1::isDraw_MC()
{
	bool result = false;
	try
	{
		result = boardGame1Logic->isDraw();
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in isDraw_MC: " + ex->Message);
		throw;
	}
	return result;
}

bool CustomBoardGamesApplicationLogicWrapping::BoardGame1::isGameOver_MC()
{
	bool result = false;
	try
	{
		result = boardGame1Logic->isGameOver();
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in isGameOver_MC: " + ex->Message);
		throw;
	}
	return result;
}

void CustomBoardGamesApplicationLogicWrapping::BoardGame1::ClearGameState_MC()
{
	try
	{
		boardGame1Logic->ClearGameState();
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in ClearGameState_MC: " + ex->Message);
		throw;
	}
}

// Game 3: 5x5 Tic-Tac-Toe
BoardGame3_Wrapper::PlayerType CustomBoardGamesApplicationLogicWrapping::BoardGame3::ConvertToNativePlayerType(
	PlayerTypeBoardGame3 playerType)
{
	switch (playerType)
	{
	case PlayerTypeBoardGame3::Human:
		return BoardGame3_Wrapper::PlayerType::Human;
	case PlayerTypeBoardGame3::Random:
		return BoardGame3_Wrapper::PlayerType::Randomizer;
	default:
		throw gcnew ArgumentException("Invalid PlayerType");
	}
}

void CustomBoardGamesApplicationLogicWrapping::BoardGame3::InitializeTheBoard_MC(String^ player1Name,
	String^ player2Name, PlayerTypeBoardGame3 player1Type, PlayerTypeBoardGame3 player2Type)
{
	try
	{
		string nativeString_Player1Name = msclr::interop::marshal_as<string>(player1Name);
		string nativeString_Player2Name = msclr::interop::marshal_as<string>(player2Name);

		boardGame3Logic->InitializeGame(nativeString_Player1Name, nativeString_Player2Name,
			ConvertToNativePlayerType(player1Type), ConvertToNativePlayerType(player2Type));
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in Initialization: " + ex->Message);
		throw;
	}
}

List<char>^ CustomBoardGamesApplicationLogicWrapping::BoardGame3::GetBoard_MC()
{
	List<char>^ boardList = gcnew List<char>();

	try
	{
		char** boardArray = boardGame3Logic->GetBoard();
		int size = 5; // Fixed 5x5 board

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
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

int CustomBoardGamesApplicationLogicWrapping::BoardGame3::GetNumberOfMovesPlayed_MC()
{
	int n_moves = -1;
	try
	{
		n_moves = boardGame3Logic->GetMovesPlayed();
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetNumberOfMovesPlayed_MC: " + ex->Message);
		throw;
	}
	return n_moves;
}

String^ CustomBoardGamesApplicationLogicWrapping::BoardGame3::GetPlayer1Name_MC()
{
	String^ playerName = gcnew String("");
	try
	{
		playerName = msclr::interop::marshal_as<String^>(boardGame3Logic->GetPlayer1Name());
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetPlayer1Name_MC: " + ex->Message);
		throw;
	}

	return playerName;
}

String^ CustomBoardGamesApplicationLogicWrapping::BoardGame3::GetPlayer2Name_MC()
{
	String^ playerName = gcnew String("");
	try
	{
		playerName = msclr::interop::marshal_as<String^>(boardGame3Logic->GetPlayer2Name());
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetPlayer2Name_MC: " + ex->Message);
		throw;
	}

	return playerName;
}

KeyValuePair<int, int>^ CustomBoardGamesApplicationLogicWrapping::BoardGame3::GetPlayer1Move_MC()
{
	try
	{
		int x, y;
		boardGame3Logic->GetPlayer1Move(x, y);
		return gcnew KeyValuePair<int, int>(x, y);
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetPlayer1Move_MC: " + ex->Message);
		throw;
	}
}

KeyValuePair<int, int>^ CustomBoardGamesApplicationLogicWrapping::BoardGame3::GetPlayer2Move_MC()
{
	try
	{
		int x, y;
		boardGame3Logic->GetPlayer2Move(x, y);
		return gcnew KeyValuePair<int, int>(x, y);
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetPlayer2Move_MC: " + ex->Message);
		throw;
	}
}

void CustomBoardGamesApplicationLogicWrapping::BoardGame3::Player1PerformMove_MC(int x, int y)
{
	try
	{
		boardGame3Logic->Player1PerformMove(x, y);
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in Player1PerformMove_MC: " + ex->Message);
		throw;
	}
}

void CustomBoardGamesApplicationLogicWrapping::BoardGame3::Player2PerformMove_MC(int x, int y)
{
	try
	{
		boardGame3Logic->Player2PerformMove(x, y);
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in Player2PerformMove_MC: " + ex->Message);
		throw;
	}
}

bool CustomBoardGamesApplicationLogicWrapping::BoardGame3::isWin_MC()
{
	bool result = false;
	try
	{
		result = boardGame3Logic->isWin();
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in isWin_MC: " + ex->Message);
		throw;
	}
	return result;
}

bool CustomBoardGamesApplicationLogicWrapping::BoardGame3::isDraw_MC()
{
	bool result = false;
	try
	{
		result = boardGame3Logic->isDraw();
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in isDraw_MC: " + ex->Message);
		throw;
	}
	return result;
}

bool CustomBoardGamesApplicationLogicWrapping::BoardGame3::isGameOver_MC()
{
	bool result = false;
	try
	{
		result = boardGame3Logic->isGameOver();
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in isGameOver_MC: " + ex->Message);
		throw;
	}
	return result;
}

void CustomBoardGamesApplicationLogicWrapping::BoardGame3::ClearGameState_MC()
{
	try
	{
		boardGame3Logic->ClearGameState();
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in ClearGameState_MC: " + ex->Message);
		throw;
	}
}

// Game 4: Word Tic-Tac-Toe
BoardGame4_Wrapper::PlayerType CustomBoardGamesApplicationLogicWrapping::BoardGame4::ConvertToNativePlayerType(
	PlayerTypeBoardGame4 playerType)
{
	switch (playerType)
	{
	case PlayerTypeBoardGame4::Human:
		return BoardGame4_Wrapper::PlayerType::Human;
	case PlayerTypeBoardGame4::Random:
		return BoardGame4_Wrapper::PlayerType::Randomizer;
	default:
		throw gcnew ArgumentException("Invalid PlayerType");
	}
}

void CustomBoardGamesApplicationLogicWrapping::BoardGame4::InitializeTheBoard_MC(String^ player1Name,
	String^ player2Name, PlayerTypeBoardGame4 player1Type, PlayerTypeBoardGame4 player2Type)
{
	try
	{
		string nativeString_Player1Name = msclr::interop::marshal_as<string>(player1Name);
		string nativeString_Player2Name = msclr::interop::marshal_as<string>(player2Name);

		boardGame4Logic->InitializeGame(nativeString_Player1Name, nativeString_Player2Name,
			ConvertToNativePlayerType(player1Type), ConvertToNativePlayerType(player2Type));
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in Initialization: " + ex->Message);
		throw;
	}
}

List<String^>^ CustomBoardGamesApplicationLogicWrapping::BoardGame4::GetBoard_MC()
{
	List<String^>^ boardList = gcnew List<String^>();

	try
	{
		string** boardArray = boardGame4Logic->GetBoard();
		int size = 3; // 3x3 board

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				boardList->Add(gcnew String(boardArray[i][j].c_str()));
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

int CustomBoardGamesApplicationLogicWrapping::BoardGame4::GetNumberOfMovesPlayed_MC()
{
	int n_moves = -1;
	try
	{
		n_moves = boardGame4Logic->GetMovesPlayed();
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetNumberOfMovesPlayed_MC: " + ex->Message);
		throw;
	}
	return n_moves;
}

String^ CustomBoardGamesApplicationLogicWrapping::BoardGame4::GetPlayer1Name_MC()
{
	String^ playerName = gcnew String("");
	try
	{
		playerName = msclr::interop::marshal_as<String^>(boardGame4Logic->GetPlayer1Name());
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetPlayer1Name_MC: " + ex->Message);
		throw;
	}

	return playerName;
}

String^ CustomBoardGamesApplicationLogicWrapping::BoardGame4::GetPlayer2Name_MC()
{
	String^ playerName = gcnew String("");
	try
	{
		playerName = msclr::interop::marshal_as<String^>(boardGame4Logic->GetPlayer2Name());
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetPlayer2Name_MC: " + ex->Message);
		throw;
	}

	return playerName;
}

KeyValuePair<int, int>^ CustomBoardGamesApplicationLogicWrapping::BoardGame4::GetPlayer1Move_MC()
{
	try
	{
		int x, y;
		boardGame4Logic->GetPlayer1Move(x, y);
		return gcnew KeyValuePair<int, int>(x, y);
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetPlayer1Move_MC: " + ex->Message);
		throw;
	}
}

KeyValuePair<int, int>^ CustomBoardGamesApplicationLogicWrapping::BoardGame4::GetPlayer2Move_MC()
{
	try
	{
		int x, y;
		boardGame4Logic->GetPlayer2Move(x, y);
		return gcnew KeyValuePair<int, int>(x, y);
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetPlayer2Move_MC: " + ex->Message);
		throw;
	}
}

void CustomBoardGamesApplicationLogicWrapping::BoardGame4::Player1PerformMove_MC(int x, int y, String^ word)
{
	try
	{
		string nativeWord = msclr::interop::marshal_as<string>(word);
		boardGame4Logic->Player1PerformMove(x, y, nativeWord);
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in Player1PerformMove_MC: " + ex->Message);
		throw;
	}
}

void CustomBoardGamesApplicationLogicWrapping::BoardGame4::Player2PerformMove_MC(int x, int y, String^ word)
{
	try
	{
		string nativeWord = msclr::interop::marshal_as<string>(word);
		boardGame4Logic->Player2PerformMove(x, y, nativeWord);
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in Player2PerformMove_MC: " + ex->Message);
		throw;
	}
}

bool CustomBoardGamesApplicationLogicWrapping::BoardGame4::ValidateWord_MC(String^ word)
{
	try
	{
		string nativeWord = msclr::interop::marshal_as<string>(word);
		return boardGame4Logic->ValidateWord(nativeWord);
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in ValidateWord_MC: " + ex->Message);
		throw;
	}
}

bool CustomBoardGamesApplicationLogicWrapping::BoardGame4::isWin_MC()
{
	bool result = false;
	try
	{
		result = boardGame4Logic->isWin();
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in isWin_MC: " + ex->Message);
		throw;
	}
	return result;
}

bool CustomBoardGamesApplicationLogicWrapping::BoardGame4::isDraw_MC()
{
	bool result = false;
	try
	{
		result = boardGame4Logic->isDraw();
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in isDraw_MC: " + ex->Message);
		throw;
	}
	return result;
}

bool CustomBoardGamesApplicationLogicWrapping::BoardGame4::isGameOver_MC()
{
	bool result = false;
	try
	{
		result = boardGame4Logic->isGameOver();
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in isGameOver_MC: " + ex->Message);
		throw;
	}
	return result;
}

void CustomBoardGamesApplicationLogicWrapping::BoardGame4::ClearGameState_MC()
{
	try
	{
		boardGame4Logic->ClearGameState();
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in ClearGameState_MC: " + ex->Message);
		throw;
	}
}

// Game 6: Misere Tic-Tac-Toe (formerly Inverse)
BoardGame6_Wrapper::PlayerType CustomBoardGamesApplicationLogicWrapping::BoardGame6::ConvertToNativePlayerType(
	PlayerTypeBoardGame6 playerType)
{
	switch (playerType)
	{
	case PlayerTypeBoardGame6::Human:
		return BoardGame6_Wrapper::PlayerType::Human;
	case PlayerTypeBoardGame6::Random:
		return BoardGame6_Wrapper::PlayerType::Randomizer;
	default:
		throw gcnew ArgumentException("Invalid PlayerType");
	}
}

void CustomBoardGamesApplicationLogicWrapping::BoardGame6::InitializeTheBoard_MC(String^ player1Name,
	String^ player2Name, PlayerTypeBoardGame6 player1Type, PlayerTypeBoardGame6 player2Type)
{
	try
	{
		string nativeString_Player1Name = msclr::interop::marshal_as<string>(player1Name);
		string nativeString_Player2Name = msclr::interop::marshal_as<string>(player2Name);

		boardGame6Logic->InitializeGame(nativeString_Player1Name, nativeString_Player2Name,
			ConvertToNativePlayerType(player1Type), ConvertToNativePlayerType(player2Type));
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in Initialization: " + ex->Message);
		throw;
	}
}

List<char>^ CustomBoardGamesApplicationLogicWrapping::BoardGame6::GetBoard_MC()
{
	List<char>^ boardList = gcnew List<char>();

	try
	{
		char** boardArray = boardGame6Logic->GetBoard();
		int size = 3; // 3x3 board

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
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

int CustomBoardGamesApplicationLogicWrapping::BoardGame6::GetNumberOfMovesPlayed_MC()
{
	int n_moves = -1;
	try
	{
		n_moves = boardGame6Logic->GetMovesPlayed();
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetNumberOfMovesPlayed_MC: " + ex->Message);
		throw;
	}
	return n_moves;
}

String^ CustomBoardGamesApplicationLogicWrapping::BoardGame6::GetPlayer1Name_MC()
{
	String^ playerName = gcnew String("");
	try
	{
		playerName = msclr::interop::marshal_as<String^>(boardGame6Logic->GetPlayer1Name());
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetPlayer1Name_MC: " + ex->Message);
		throw;
	}

	return playerName;
}

String^ CustomBoardGamesApplicationLogicWrapping::BoardGame6::GetPlayer2Name_MC()
{
	String^ playerName = gcnew String("");
	try
	{
		playerName = msclr::interop::marshal_as<String^>(boardGame6Logic->GetPlayer2Name());
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetPlayer2Name_MC: " + ex->Message);
		throw;
	}

	return playerName;
}

KeyValuePair<int, int>^ CustomBoardGamesApplicationLogicWrapping::BoardGame6::GetPlayer1Move_MC()
{
	try
	{
		int x, y;
		boardGame6Logic->GetPlayer1Move(x, y);
		return gcnew KeyValuePair<int, int>(x, y);
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetPlayer1Move_MC: " + ex->Message);
		throw;
	}
}

KeyValuePair<int, int>^ CustomBoardGamesApplicationLogicWrapping::BoardGame6::GetPlayer2Move_MC()
{
	try
	{
		int x, y;
		boardGame6Logic->GetPlayer2Move(x, y);
		return gcnew KeyValuePair<int, int>(x, y);
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetPlayer2Move_MC: " + ex->Message);
		throw;
	}
}

void CustomBoardGamesApplicationLogicWrapping::BoardGame6::Player1PerformMove_MC(int x, int y)
{
	try
	{
		boardGame6Logic->Player1PerformMove(x, y);
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in Player1PerformMove_MC: " + ex->Message);
		throw;
	}
}

void CustomBoardGamesApplicationLogicWrapping::BoardGame6::Player2PerformMove_MC(int x, int y)
{
	try
	{
		boardGame6Logic->Player2PerformMove(x, y);
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in Player2PerformMove_MC: " + ex->Message);
		throw;
	}
}

bool CustomBoardGamesApplicationLogicWrapping::BoardGame6::isWin_MC()
{
	bool result = false;
	try
	{
		result = boardGame6Logic->isWin();
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in isWin_MC: " + ex->Message);
		throw;
	}
	return result;
}

bool CustomBoardGamesApplicationLogicWrapping::BoardGame6::isDraw_MC()
{
	bool result = false;
	try
	{
		result = boardGame6Logic->isDraw();
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in isDraw_MC: " + ex->Message);
		throw;
	}
	return result;
}

bool CustomBoardGamesApplicationLogicWrapping::BoardGame6::isGameOver_MC()
{
	bool result = false;
	try
	{
		result = boardGame6Logic->isGameOver();
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in isGameOver_MC: " + ex->Message);
		throw;
	}
	return result;
}

void CustomBoardGamesApplicationLogicWrapping::BoardGame6::ClearGameState_MC()
{
	try
	{
		boardGame6Logic->ClearGameState();
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in ClearGameState_MC: " + ex->Message);
		throw;
	}
}

// Game 8: Ultimate Tic-Tac-Toe
BoardGame8_Wrapper::PlayerType CustomBoardGamesApplicationLogicWrapping::BoardGame8::ConvertToNativePlayerType(
	PlayerTypeBoardGame8 playerType)
{
	switch (playerType)
	{
	case PlayerTypeBoardGame8::Human:
		return BoardGame8_Wrapper::PlayerType::Human;
	case PlayerTypeBoardGame8::Random:
		return BoardGame8_Wrapper::PlayerType::Randomizer;
	default:
		throw gcnew ArgumentException("Invalid PlayerType");
	}
}

void CustomBoardGamesApplicationLogicWrapping::BoardGame8::InitializeTheBoard_MC(String^ player1Name,
	String^ player2Name, PlayerTypeBoardGame8 player1Type, PlayerTypeBoardGame8 player2Type)
{
	try
	{
		string nativeString_Player1Name = msclr::interop::marshal_as<string>(player1Name);
		string nativeString_Player2Name = msclr::interop::marshal_as<string>(player2Name);

		boardGame8Logic->InitializeGame(nativeString_Player1Name, nativeString_Player2Name,
			ConvertToNativePlayerType(player1Type), ConvertToNativePlayerType(player2Type));
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in Initialization: " + ex->Message);
		throw;
	}
}

List<char>^ CustomBoardGamesApplicationLogicWrapping::BoardGame8::GetBoard_MC()
{
	List<char>^ boardList = gcnew List<char>();

	try
	{
		char** boardArray = boardGame8Logic->GetBoard();
		int size = 9; // 9x9 board for Ultimate

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
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

List<char>^ CustomBoardGamesApplicationLogicWrapping::BoardGame8::GetBigBoard_MC()
{
	List<char>^ bigBoardList = gcnew List<char>();

	try
	{
		char** bigBoardArray = boardGame8Logic->GetBigBoard();
		int size = 3; // 3x3 big board

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				bigBoardList->Add(bigBoardArray[i][j]);
			}
		}
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetBigBoard_MC: " + ex->Message);
		throw;
	}

	return bigBoardList;
}

bool CustomBoardGamesApplicationLogicWrapping::BoardGame8::IsSubBoardComplete_MC(int boardIndex)
{
	try
	{
		return boardGame8Logic->IsSubBoardComplete(boardIndex);
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in IsSubBoardComplete_MC: " + ex->Message);
		throw;
	}
}

int CustomBoardGamesApplicationLogicWrapping::BoardGame8::GetCurrentBoard_MC()
{
	try
	{
		return boardGame8Logic->GetCurrentBoard();
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetCurrentBoard_MC: " + ex->Message);
		throw;
	}
}

int CustomBoardGamesApplicationLogicWrapping::BoardGame8::GetNumberOfMovesPlayed_MC()
{
	int n_moves = -1;
	try
	{
		n_moves = boardGame8Logic->GetMovesPlayed();
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetNumberOfMovesPlayed_MC: " + ex->Message);
		throw;
	}
	return n_moves;
}

String^ CustomBoardGamesApplicationLogicWrapping::BoardGame8::GetPlayer1Name_MC()
{
	String^ playerName = gcnew String("");
	try
	{
		playerName = msclr::interop::marshal_as<String^>(boardGame8Logic->GetPlayer1Name());
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetPlayer1Name_MC: " + ex->Message);
		throw;
	}

	return playerName;
}

String^ CustomBoardGamesApplicationLogicWrapping::BoardGame8::GetPlayer2Name_MC()
{
	String^ playerName = gcnew String("");
	try
	{
		playerName = msclr::interop::marshal_as<String^>(boardGame8Logic->GetPlayer2Name());
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetPlayer2Name_MC: " + ex->Message);
		throw;
	}

	return playerName;
}

KeyValuePair<int, int>^ CustomBoardGamesApplicationLogicWrapping::BoardGame8::GetPlayer1Move_MC()
{
	try
	{
		int x, y;
		boardGame8Logic->GetPlayer1Move(x, y);
		return gcnew KeyValuePair<int, int>(x, y);
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetPlayer1Move_MC: " + ex->Message);
		throw;
	}
}

KeyValuePair<int, int>^ CustomBoardGamesApplicationLogicWrapping::BoardGame8::GetPlayer2Move_MC()
{
	try
	{
		int x, y;
		boardGame8Logic->GetPlayer2Move(x, y);
		return gcnew KeyValuePair<int, int>(x, y);
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in GetPlayer2Move_MC: " + ex->Message);
		throw;
	}
}

void CustomBoardGamesApplicationLogicWrapping::BoardGame8::Player1PerformMove_MC(int x, int y)
{
	try
	{
		boardGame8Logic->Player1PerformMove(x, y);
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in Player1PerformMove_MC: " + ex->Message);
		throw;
	}
}

void CustomBoardGamesApplicationLogicWrapping::BoardGame8::Player2PerformMove_MC(int x, int y)
{
	try
	{
		boardGame8Logic->Player2PerformMove(x, y);
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in Player2PerformMove_MC: " + ex->Message);
		throw;
	}
}

bool CustomBoardGamesApplicationLogicWrapping::BoardGame8::isWin_MC()
{
	bool result = false;
	try
	{
		result = boardGame8Logic->isWin();
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in isWin_MC: " + ex->Message);
		throw;
	}
	return result;
}

bool CustomBoardGamesApplicationLogicWrapping::BoardGame8::isDraw_MC()
{
	bool result = false;
	try
	{
		result = boardGame8Logic->isDraw();
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in isDraw_MC: " + ex->Message);
		throw;
	}
	return result;
}

bool CustomBoardGamesApplicationLogicWrapping::BoardGame8::isGameOver_MC()
{
	bool result = false;
	try
	{
		result = boardGame8Logic->isGameOver();
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in isGameOver_MC: " + ex->Message);
		throw;
	}
	return result;
}

void CustomBoardGamesApplicationLogicWrapping::BoardGame8::ClearGameState_MC()
{
	try
	{
		boardGame8Logic->ClearGameState();
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error occurred in ClearGameState_MC: " + ex->Message);
		throw;
	}
}

// Common IsValidMove_MC implementation for all games
bool CustomBoardGamesApplicationLogicWrapping::BoardGame1::IsValidMove_MC(int x, int y)
{
    try
    {
        return boardGame1Logic->IsValidMove(x, y);
    }
    catch (Exception^ ex)
    {
        Console::WriteLine("Error occurred in IsValidMove_MC: " + ex->Message);
        throw;
    }
}

bool CustomBoardGamesApplicationLogicWrapping::BoardGame2::IsValidMove_MC(int x, int y)
{
    try
    {
        return boardGame2Logic->IsValidMove(x, y);
    }
    catch (Exception^ ex)
    {
        Console::WriteLine("Error occurred in IsValidMove_MC: " + ex->Message);
        throw;
    }
}

bool CustomBoardGamesApplicationLogicWrapping::BoardGame3::IsValidMove_MC(int x, int y)
{
    try
    {
        return boardGame3Logic->IsValidMove(x, y);
    }
    catch (Exception^ ex)
    {
        Console::WriteLine("Error occurred in IsValidMove_MC: " + ex->Message);
        throw;
    }
}

bool CustomBoardGamesApplicationLogicWrapping::BoardGame4::IsValidMove_MC(int x, int y)
{
    try
    {
        return boardGame4Logic->IsValidMove(x, y);
    }
    catch (Exception^ ex)
    {
        Console::WriteLine("Error occurred in IsValidMove_MC: " + ex->Message);
        throw;
    }
}

bool CustomBoardGamesApplicationLogicWrapping::BoardGame5::IsValidMove_MC(int x, int y)
{
    try
    {
        return boardGame5Logic->IsValidMove(x, y);
    }
    catch (Exception^ ex)
    {
        Console::WriteLine("Error occurred in IsValidMove_MC: " + ex->Message);
        throw;
    }
}

bool CustomBoardGamesApplicationLogicWrapping::BoardGame6::IsValidMove_MC(int x, int y)
{
    try
    {
        return boardGame6Logic->IsValidMove(x, y);
    }
    catch (Exception^ ex)
    {
        Console::WriteLine("Error occurred in IsValidMove_MC: " + ex->Message);
        throw;
    }
}

bool CustomBoardGamesApplicationLogicWrapping::BoardGame7::IsValidMove_MC(int x, int y)
{
    try
    {
        return boardGame7Logic->IsValidMove(x, y);
    }
    catch (Exception^ ex)
    {
        Console::WriteLine("Error occurred in IsValidMove_MC: " + ex->Message);
        throw;
    }
}

bool CustomBoardGamesApplicationLogicWrapping::BoardGame8::IsValidMove_MC(int x, int y)
{
    try
    {
        return boardGame8Logic->IsValidMove(x, y);
    }
    catch (Exception^ ex)
    {
        Console::WriteLine("Error occurred in IsValidMove_MC: " + ex->Message);
        throw;
    }
}

// Disposal patterns for all games

public ref class BoardGame2
{
private:
    bool disposed;
    
public:
    BoardGame2() : disposed(false) 
    {
        boardGame2Logic = new BoardGame2_Wrapper();
    }
    
    ~BoardGame2()
    {
        if (!disposed)
        {
            this->!BoardGame2();
            disposed = true;
        }
    }
    
    !BoardGame2()
    {
        if (boardGame2Logic != nullptr)
        {
            delete boardGame2Logic;
            boardGame2Logic = nullptr;
        }
    }
};

public ref class BoardGame3
{
private:
    bool disposed;
    
public:
    BoardGame3() : disposed(false) 
    {
        boardGame3Logic = new BoardGame3_Wrapper();
    }
    
    ~BoardGame3()
    {
        if (!disposed)
        {
            this->!BoardGame3();
            disposed = true;
        }
    }
    
    !BoardGame3()
    {
        if (boardGame3Logic != nullptr)
        {
            delete boardGame3Logic;
            boardGame3Logic = nullptr;
        }
    }
};

public ref class BoardGame4
{
private:
    bool disposed;
    
public:
    BoardGame4() : disposed(false) 
    {
        boardGame4Logic = new BoardGame4_Wrapper();
    }
    
    ~BoardGame4()
    {
        if (!disposed)
        {
            this->!BoardGame4();
            disposed = true;
        }
    }
    
    !BoardGame4()
    {
        if (boardGame4Logic != nullptr)
        {
            delete boardGame4Logic;
            boardGame4Logic = nullptr;
        }
    }
};

public ref class BoardGame5
{
private:
    bool disposed;
    
public:
    BoardGame5() : disposed(false) 
    {
        boardGame5Logic = new BoardGame5_Wrapper();
    }
    
    ~BoardGame5()
    {
        if (!disposed)
        {
            this->!BoardGame5();
            disposed = true;
        }
    }
    
    !BoardGame5()
    {
        if (boardGame5Logic != nullptr)
        {
            delete boardGame5Logic;
            boardGame5Logic = nullptr;
        }
    }
};

public ref class BoardGame6
{
private:
    bool disposed;
    
public:
    BoardGame6() : disposed(false) 
    {
        boardGame6Logic = new BoardGame6_Wrapper();
    }
    
    ~BoardGame6()
    {
        if (!disposed)
        {
            this->!BoardGame6();
            disposed = true;
        }
    }
    
    !BoardGame6()
    {
        if (boardGame6Logic != nullptr)
        {
            delete boardGame6Logic;
            boardGame6Logic = nullptr;
        }
    }
};

public ref class BoardGame7
{
private:
    bool disposed;
    
public:
    BoardGame7() : disposed(false) 
    {
        boardGame7Logic = new BoardGame7_Wrapper();
    }
    
    ~BoardGame7()
    {
        if (!disposed)
        {
            this->!BoardGame7();
            disposed = true;
        }
    }
    
    !BoardGame7()
    {
        if (boardGame7Logic != nullptr)
        {
            delete boardGame7Logic;
            boardGame7Logic = nullptr;
        }
    }
};

public ref class BoardGame8
{
private:
    bool disposed;
    
public:
    BoardGame8() : disposed(false) 
    {
        boardGame8Logic = new BoardGame8_Wrapper();
    }
    
    ~BoardGame8()
    {
        if (!disposed)
        {
            this->!BoardGame8();
            disposed = true;
        }
    }
    
    !BoardGame8()
    {
        if (boardGame8Logic != nullptr)
        {
            delete boardGame8Logic;
            boardGame8Logic = nullptr;
        }
    }
};
