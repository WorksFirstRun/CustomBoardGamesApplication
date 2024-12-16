// BoardGamesGUI.h
#pragma once
#include <GLFW/glfw3.h>
#include "GameLogic/BoardGame7_Wrapper.h"
#include "GameLogic/UltimateTTT_Wrapper.h"
#include <memory>
#include <utility>

class BoardGamesGUI {
public:
    BoardGamesGUI();
    ~BoardGamesGUI();

    bool init();
    void render();

    bool isGameOver() const {
        if (currentGame == Game4x4) {

        } else if (currentGame == GameUltimate) {
            return gameUltimate->is_win() || gameUltimate->isDraw();
        }
        return false;
    }

private:
    // Window management
    GLFWwindow* window;
    float dpiScale;

    // Game selection
    enum GameType {
        NoGame,
        Game4x4,
        GameUltimate
    } currentGame;

    // Game state
    struct GameState {
        std::string player1Name;
        std::string player2Name;
        BoardGame7_Wrapper::PlayerType player1Type;
        BoardGame7_Wrapper::PlayerType player2Type;
    } gameState;

    // Game instances
    std::unique_ptr<BoardGame7_Wrapper> game4x4;
    std::unique_ptr<UltimateTTT_Wrapper> gameUltimate;

    // Game state variables
    bool gameStarted;
    bool isPlayer1Turn;
    std::pair<int, int> selectedTokenPos;
    std::string errorMessage;

    // UI State
    bool showPlayerSetup;
    bool showGameWindow;

    // UI Methods
    void renderMainMenu();
    void renderPlayerSetupDialog();
    void render4x4Game();
    void renderUltimateGame();

    // Game logic methods
    void handleTokenSelection(int x, int y);
    void handleTokenMove(int x, int y);

    // Helper methods
    void setupStyle();
    void cleanup();
    void startGame(const std::string& p1Name, const std::string& p2Name,
                  BoardGame7_Wrapper::PlayerType p1Type,
                  BoardGame7_Wrapper::PlayerType p2Type);

    bool isCurrentPlayerComputer() const {
        return (isPlayer1Turn && gameState.player1Type == BoardGame7_Wrapper::Randomizer) ||
               (!isPlayer1Turn && gameState.player2Type == BoardGame7_Wrapper::Randomizer);
    }

    static constexpr float MENU_BUTTON_WIDTH = 400.0f;
    static constexpr float BUTTON_HEIGHT = 50.0f;
    static constexpr float PADDING = 15.0f;
    static constexpr float CELL_SIZE = 100.0f;
    static constexpr float GAME_BUTTON_WIDTH = 200.0f;
};