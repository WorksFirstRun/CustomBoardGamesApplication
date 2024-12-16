#pragma once
#include "FourByFourTicTacToe.h"
#include <vector>
#include <random>
#include <ctime>
#include <memory>

class BoardGame7_Wrapper {
public:
    enum PlayerType {
        Human,
        Randomizer
    };

    BoardGame7_Wrapper() : board(nullptr) {
        board = std::make_unique<FourByFourTTT_Board<Token>>();
        srand(static_cast<unsigned>(time(nullptr)));
    }

    void InitializeGame(std::string player1, std::string player2,
                       PlayerType player1Type, PlayerType player2Type) {
        this->player1Type = player1Type;
        this->player2Type = player2Type;
        isPlayer1Turn = true;
        moveMadeThisTurn = false;
        selectedTokenPos = {-1, -1};
        gameOver = false;

        // Player 1 (X) tokens on top two rows
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 4; j++) {
                Token token;
                token.SetSymbol('X');
                token.currentPosition = {i, j};
                board->update_board(i, j, token);  // Simplified without isValidMove check
            }
        }

        // Player 2 (O) tokens on bottom two rows
        for (int i = 2; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                Token token;
                token.SetSymbol('O');
                token.currentPosition = {i, j};
                board->update_board(i, j, token);  // Simplified without isValidMove check
            }
        }
    }

    std::pair<int, int> getComputerMove() {
        if (selectedTokenPos.first == -1) {
            // First phase: Select a token
            auto* board4x4 = dynamic_cast<FourByFourTTT_Board<Token>*>(board.get());
            vector<Token*> tokensReference;
            char playerSymbol = isPlayer1Turn ? 'X' : 'O';

            // Get all valid tokens for current player
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    Token* token = board4x4->GetTokenAtPosition(i, j);
                    if (token && token->GetSymbol() == playerSymbol) {
                        tokensReference.push_back(token);
                    }
                }
            }

            // Select a random token that has valid moves
            while (!tokensReference.empty()) {
                int randomIndex = rand() % tokensReference.size();
                Token* randomToken = tokensReference[randomIndex];
                auto currentPos = randomToken->GetCurrentPosition();
                
                // Check if this token has any valid moves
                vector<pair<int,int>> directions = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
                for (auto dir : directions) {
                    int newX = currentPos.first + dir.first;
                    int newY = currentPos.second + dir.second;
                    if (newX >= 0 && newX <= 3 && newY >= 0 && newY <= 3 &&
                        board4x4->isValidMove(newX, newY, *randomToken)) {
                        selectedTokenPos = currentPos;
                        return currentPos;  // Return the selected token position
                    }
                }
                
                // Remove token if it has no valid moves
                tokensReference.erase(tokensReference.begin() + randomIndex);
            }
        } else {
            // Second phase: Make the move
            auto* board4x4 = dynamic_cast<FourByFourTTT_Board<Token>*>(board.get());
            Token* token = board4x4->GetTokenAtPosition(selectedTokenPos.first, selectedTokenPos.second);
            
            vector<pair<int,int>> directions = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
            vector<pair<int,int>> validMoves;

            for (auto dir : directions) {
                int newX = selectedTokenPos.first + dir.first;
                int newY = selectedTokenPos.second + dir.second;
                if (newX >= 0 && newX <= 3 && newY >= 0 && newY <= 3 &&
                    board4x4->isValidMove(newX, newY, *token)) {
                    validMoves.push_back({newX, newY});
                }
            }

            if (!validMoves.empty()) {
                auto move = validMoves[rand() % validMoves.size()];
                return move;
            }
        }

        return {-1, -1};
    }

    bool makeMove(int x, int y) {
        if (isGameOver()) return false;

        Token* token = board->GetTokenAtPosition(selectedTokenPos.first, selectedTokenPos.second);
        char currentPlayerSymbol = isPlayer1Turn ? 'X' : 'O';

        if (selectedTokenPos.first == -1) {
            // First phase: Select a token
            token = board->GetTokenAtPosition(x, y);
            if (token && token->GetSymbol() == currentPlayerSymbol) {
                selectedTokenPos = {x, y};
                moveMadeThisTurn = false;
                return true;
            }
        } else {
            // Second phase: Move the token
            if (token && token->GetSymbol() == currentPlayerSymbol) {
                if (board->isValidMove(x, y, *token)) {
                    token->SetPosition({x, y});
                    selectedTokenPos = {-1, -1};
                    moveMadeThisTurn = true;
                    isPlayer1Turn = !isPlayer1Turn;  // Switch turns
                    
                    // Check for win condition after move
                    if (board->is_win()) {
                        gameOver = true;
                        // The winner is the player who just made the move
                        winner = !isPlayer1Turn;  // Since we already switched turns
                    }
                    return true;
                } else {
                    // Allow selecting a different token
                    Token* newToken = board->GetTokenAtPosition(x, y);
                    if (newToken && newToken->GetSymbol() == currentPlayerSymbol) {
                        selectedTokenPos = {x, y};
                        moveMadeThisTurn = false;
                        return true;
                    }
                }
            }
        }
        return false;
    }

    void Player1PerformMove(int x, int y) {
        if (!isPlayer1Turn) return;
        makeMove(x, y);
    }

    void Player2PerformMove(int x, int y) {
        if (isPlayer1Turn) return;
        makeMove(x, y);
    }

    bool is_win() const {
        return board->is_win();
    }

    bool isDraw() const {
        return board->is_draw();
    }

    char getSymbolAt(int x, int y) const {
        Token* token = board->GetTokenAtPosition(x, y);
        return token ? token->GetSymbol() : ' ';
    }

    bool wasMoveMade() const {
        return moveMadeThisTurn;
    }

    void resetMove() {
        selectedTokenPos = {-1, -1};
        moveMadeThisTurn = false;
    }

    bool isCurrentPlayerTurn(bool isPlayer1) const {
        return isPlayer1 == isPlayer1Turn;
    }

    bool getCurrentTurn() const {
        return isPlayer1Turn;
    }

    bool makeComputerMove() {
        if (gameOver) {
            return false;  // Game is already over, don't make a move
        }

        auto move = getComputerMove();
        if (move.first != -1 && move.second != -1) {
            // Move the selected token to the new position
            Token* token = board->GetTokenAtPosition(selectedTokenPos.first, selectedTokenPos.second);
            if (token) {
                token->SetPosition({move.first, move.second});
                board->update_board(move.first, move.second, *token);
                moveMadeThisTurn = true;
                return true;
            }
        }
        return false;
    }

    bool isGameOver() const {
        return board->is_win() || board->is_draw();
    }

    void setGameOver(bool value) {
        gameOver = value;
    }

    bool getWinner() const {
        return winner;
    }

private:
    std::unique_ptr<FourByFourTTT_Board<Token>> board;
    PlayerType player1Type;
    PlayerType player2Type;
    bool isPlayer1Turn = true;
    bool moveMadeThisTurn = false;
    std::pair<int, int> selectedTokenPos = {-1, -1};
    std::pair<int, int> lastMove = {-1, -1};  // Track the last move
    bool gameOver = false;
    bool winner = false;  // true for Player 1, false for Player 2
};
