#include "pch.h"
#include "../CustomBoardGamesApplication/BoardGame_2/Four_in_a_Row.h"
#include <msclr/marshal_cppstd.h>
using namespace System;
using namespace System::Collections::Generic;

namespace CustomBoardGamesApplicationLogicWrapping {
	public ref class BoardGame2
	{
	private:
		BoardGame2_Wrapper * boardGame2Logic;
	public:



		enum class PlayerTypeBoardGame2
		{
			Human,
			RandomPlayer,
			Ai
		};

		BoardGame2_Wrapper::PlayerType ConvertToNativePlayerType(PlayerTypeBoardGame2 playerType);


		BoardGame2() {
			boardGame2Logic = new BoardGame2_Wrapper();
		}

		~BoardGame2()
		{
			this->!BoardGame2();
		}

		!BoardGame2()
		{
			delete boardGame2Logic;
		}


		void InitializeTheBoard_MC(String ^ player1Name,String ^ player2Name,PlayerTypeBoardGame2 player1Type, PlayerTypeBoardGame2 player2Type);
		List<char> ^ GetBoard_MC();
		int GetNumberOfMovesPlayed_MC();
		List<int> ^ GetCurrentRowOfEachColumn_MC();
		String^ GetPlayer1Name_MC();
		String^ GetPlayer2Name_MC();
		KeyValuePair<int,int> ^ GetPlayer1Move_MC();
		KeyValuePair<int, int>^ GetPlayer2Move_MC();
		void Player1PerformMove_MC(int x, int y);
		void Player2PerformMove_MC(int x, int y);
		bool isWin_MC();
		bool isDraw_MC();
		bool isGameOver_MC();
		void ClearGameState_MC();
	};
}
