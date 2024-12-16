#pragma once
#include "Ultimate_Tic-Tac-Toe.h"
#include <memory>
#include <stdexcept>
#include <iostream>

class UltimateTTT_Wrapper {
public:
    enum PlayerType {
        Human,
        Randomizer
    };

    UltimateTTT_Wrapper() : board(nullptr) {
        board = std::make_unique<Ultimate_grid<char>>();
    }

    void InitializeGame(const std::string& player1Name, const std::string& player2Name,
                        PlayerType player1Type, PlayerType player2Type) {
        board = std::make_unique<Ultimate_grid<char>>();
        this->player1Type = player1Type;
        this->player2Type = player2Type;
        isPlayer1Turn = true;
        nextValidSubGrid = -1;
    }

    char getSymbolAt(int x, int y) const {
        int subGrid = (x / 3) * 3 + (y / 3);
        int localX = x % 3;
        int localY = y % 3;

        return board->Big_board[subGrid]->get_symbol(localX, localY);
    }

    char getSubGridWinner(int subGrid) const {
        return board->Win[subGrid];
    }

    void Player1PerformMove(int x, int y) {
        if (!isPlayer1Turn || isGameOver()) return;
        performMove(x, y, 'X');
    }

    void Player2PerformMove(int x, int y) {
        if (isPlayer1Turn || isGameOver()) return;
        performMove(x, y, 'O');
    }

    std::pair<int, int> getComputerMove() {
        if (isGameOver()) return {-1, -1};
        
        std::vector<std::pair<int, int>> validMoves;
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                int subGrid = (i / 3) * 3 + (j / 3);
                if (board->Win[subGrid] == ' ' && 
                    board->Big_board[subGrid]->get_symbol(i % 3, j % 3) == ' ') {
                    validMoves.push_back({i, j});
                }
            }
        }

        if (!validMoves.empty()) {
            int randomIndex = rand() % validMoves.size();
            return validMoves[randomIndex];
        }
        
        return {-1, -1};
    }

    bool isValidMove(int x, int y, char symbol) const {
        if (x < 0 || x >= 9 || y < 0 || y >= 9) return false;

        int subGrid = (x / 3) * 3 + (y / 3);
        int localX = x % 3;
        int localY = y % 3;

        if (nextValidSubGrid != -1 && subGrid != nextValidSubGrid) {
            return false;
        }

        if (board->Win[subGrid] != ' ') {
            return false;
        }

        return board->Big_board[subGrid]->get_symbol(localX, localY) == ' ';
    }

    bool is_win() const {
        return board->is_win();
    }

    bool isDraw() const {
        return board->is_draw();
    }

    bool getCurrentTurn() const {
        return isPlayer1Turn;
    }

    int getNextValidSubGrid() const {
        return nextValidSubGrid;
    }

    bool isGameOver() const {
        return board->is_win() || board->is_draw();
    }

private:
    void performMove(int x, int y, char symbol) {
        if (x < 0 || x >= 9 || y < 0 || y >= 9) {
            throw std::runtime_error("Invalid move: Out of bounds");
        }

        int subGrid = (x / 3) * 3 + (y / 3);
        
        if (board->Win[subGrid] != ' ') {
            throw std::runtime_error("Invalid move: Grid already won");
        }

        if (board->Big_board[subGrid]->get_symbol(x % 3, y % 3) != ' ') {
            throw std::runtime_error("Invalid move: Cell already occupied");
        }

        if (!board->update_board(x, y, symbol)) {
            throw std::runtime_error("Move failed");
        }

        isPlayer1Turn = !isPlayer1Turn;
    }

    std::unique_ptr<Ultimate_grid<char>> board;
    PlayerType player1Type;
    PlayerType player2Type;
    bool isPlayer1Turn;
    int nextValidSubGrid;
}; 