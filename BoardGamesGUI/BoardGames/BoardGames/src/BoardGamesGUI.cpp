#define IMGUI_IMPL_OPENGL_LOADER_GLAD

#include "BoardGamesGUI.h"
#include <glad/glad.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include "imgui.h"
#include <iostream>
#include <stdexcept>

BoardGamesGUI::BoardGamesGUI() :
    window(nullptr),
    dpiScale(1.0f),
    currentGame(NoGame),
    showPlayerSetup(false),
    showGameWindow(false),
    gameStarted(false),
    isPlayer1Turn(true),
    selectedTokenPos({-1, -1}),
    errorMessage("") {

    gameState = GameState{
        "Player 1",
        "Player 2",
        BoardGame7_Wrapper::Human,
        BoardGame7_Wrapper::Human
    };
}

BoardGamesGUI::~BoardGamesGUI() {
    game4x4.reset();
    cleanup();
}

bool BoardGamesGUI::init() {
    if (!glfwInit()) {
        return false;
    }

    window = glfwCreateWindow(1280, 720, "Board Games", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cleanup();
        return false;
    }

    // Initialize Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Setup DPI scaling
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    if (monitor) {
        float xscale, yscale;
        glfwGetMonitorContentScale(monitor, &xscale, &yscale);
        dpiScale = xscale;
    }

    setupStyle();

    // Load fonts
    ImGuiIO& io = ImGui::GetIO();
    
    // Method 1: Load default font with larger size
    io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 24.0f);
    
    // Method 2: Merge icons/symbols with main font
    static const ImWchar icons_ranges[] = { 0x2500, 0x25FF, 0 }; // Example range for box drawing
    ImFontConfig icons_config; 
    icons_config.MergeMode = true;
    io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\seguisym.ttf", 24.0f, &icons_config, icons_ranges);

    // Method 3: Load Google fonts or other custom fonts
    // io.Fonts->AddFontFromFileTTF("path/to/your/font.ttf", 24.0f);

    // Build font atlas
    io.Fonts->Build();

    return true;
}

void BoardGamesGUI::render() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::Begin("MainWindow", nullptr,
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoScrollbar |
            ImGuiWindowFlags_NoScrollWithMouse |
            ImGuiWindowFlags_NoBringToFrontOnFocus);

        if (!showGameWindow) {
            renderMainMenu();
        } else {
            if (currentGame == Game4x4) {
                render4x4Game();
            } else if (currentGame == GameUltimate) {
                renderUltimateGame();
            }
        }

        ImGui::End();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
}

void BoardGamesGUI::renderMainMenu() {
    ImVec2 windowSize = ImGui::GetWindowSize();
    ImVec2 buttonSize(MENU_BUTTON_WIDTH, BUTTON_HEIGHT * 2);  // Make height double for menu buttons
    float spacing = PADDING * 2;

    float totalWidth = buttonSize.x * 2 + spacing;
    float startX = (windowSize.x - totalWidth) * 0.5f;
    float startY = (windowSize.y - buttonSize.y) * 0.5f;

    ImGui::SetCursorPos(ImVec2(startX, startY));
    if (ImGui::Button("4 x 4 Tic-Tac-Toe", buttonSize)) {
        currentGame = Game4x4;
        showPlayerSetup = true;
    }

    ImGui::SetCursorPos(ImVec2(startX + buttonSize.x + spacing, startY));
    if (ImGui::Button("Ultimate Tic-Tac-Toe", buttonSize)) {
        currentGame = GameUltimate;
        showPlayerSetup = true;
    }

    if (showPlayerSetup) {
        ImGui::OpenPopup("Player Setup");
        renderPlayerSetupDialog();
    }
}

void BoardGamesGUI::renderPlayerSetupDialog() {
    static char player1Name[128] = "Player 1";
    static char player2Name[128] = "Player 2";
    static int player1Type = 0; // 0 = Human, 1 = Computer
    static int player2Type = 0;

    if (ImGui::BeginPopupModal("Player Setup", &showPlayerSetup,
        ImGuiWindowFlags_AlwaysAutoResize)) {

        ImGui::Text("Player 1 Setup");
        ImGui::Separator();
        ImGui::RadioButton("Human##1", &player1Type, 0); ImGui::SameLine();
        ImGui::RadioButton("Computer##1", &player1Type, 1);
        ImGui::InputText("Name##1", player1Name, IM_ARRAYSIZE(player1Name));

        ImGui::Spacing();
        ImGui::Text("Player 2 Setup");
        ImGui::Separator();
        ImGui::RadioButton("Human##2", &player2Type, 0); ImGui::SameLine();
        ImGui::RadioButton("Computer##2", &player2Type, 1);
        ImGui::InputText("Name##2", player2Name, IM_ARRAYSIZE(player2Name));

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        if (ImGui::Button("Start Game", ImVec2(120, 40))) {
            startGame(player1Name, player2Name,
                     player1Type == 0 ? BoardGame7_Wrapper::Human : BoardGame7_Wrapper::Randomizer,
                     player2Type == 0 ? BoardGame7_Wrapper::Human : BoardGame7_Wrapper::Randomizer);
            showPlayerSetup = false;
            showGameWindow = true;
            ImGui::CloseCurrentPopup();
        }

        ImGui::SameLine();
        if (ImGui::Button("Cancel", ImVec2(120, 40))) {
            showPlayerSetup = false;
            currentGame = NoGame;
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}

void BoardGamesGUI::render4x4Game() {
    if (!game4x4 || !gameStarted) return;

    // Handle computer moves
    if (isCurrentPlayerComputer()) {
        static float lastMoveTime = 0.0f;
        float currentTime = ImGui::GetTime();

        if (currentTime - lastMoveTime > 0.5f) {
            // If no token is selected yet
            if (selectedTokenPos.first == -1) {
                std::pair<int, int> move = game4x4->getComputerMove();
                if (move.first != -1 && move.second != -1) {
                    // First select the token
                    selectedTokenPos = move;  // Store the selected token position
                }
            } 
            // If token is selected, make the move
            else {
                std::pair<int, int> move = game4x4->getComputerMove();
                if (move.first != -1 && move.second != -1) {
                    try {
                        if (isPlayer1Turn) {
                            game4x4->Player1PerformMove(move.first, move.second);
                        } else {
                            game4x4->Player2PerformMove(move.first, move.second);
                        }
                        
                        // Important: Update turn state after successful move
                        isPlayer1Turn = !isPlayer1Turn;  // Switch turns explicitly
                        lastMoveTime = currentTime;
                        selectedTokenPos = {-1, -1};  // Reset selected token
                        errorMessage = "";  // Clear any error messages
                    } catch (const std::exception& e) {
                        errorMessage = e.what();
                        selectedTokenPos = {-1, -1};  // Reset on error
                    }
                }
            }
        }
    }

    // Game status bar
    ImVec2 contentRegion = ImGui::GetContentRegionAvail();
    std::string playerText = "Current Player: " + 
        std::string(isPlayer1Turn ? gameState.player1Name : gameState.player2Name);
    float textWidth = ImGui::CalcTextSize(playerText.c_str()).x;
    float textPadding = (contentRegion.x - textWidth) * 0.5f;
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + textPadding);
    ImGui::Text("%s", playerText.c_str());

    if (!errorMessage.empty()) {
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
        ImGui::Text("%s", errorMessage.c_str());
        ImGui::PopStyleColor();
    }

    // Game board
    float windowWidth = std::min(contentRegion.x, 600.0f);
    float cellSize = std::min(80.0f, windowWidth / 4.0f);
    float totalWidth = (cellSize * 4) + (PADDING * 3);
    float leftPadding = (contentRegion.x - totalWidth) * 0.5f;

    for (int i = 0; i < 4; i++) {
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + leftPadding);
        
        for (int j = 0; j < 4; j++) {
            if (j > 0) ImGui::SameLine(0.0f, PADDING);

            ImGui::PushID(i * 4 + j);
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20, 20));

            char symbol = game4x4->getSymbolAt(i, j);
            std::string buttonLabel = symbol == ' ' ? "##empty" : std::string(1, symbol);

            if (ImGui::Button(buttonLabel.c_str(), ImVec2(cellSize, cellSize))) {
                if (!isCurrentPlayerComputer()) {
                    try {
                        if (isPlayer1Turn) {
                            game4x4->Player1PerformMove(i, j);
                        } else {
                            game4x4->Player2PerformMove(i, j);
                        }
                        isPlayer1Turn = game4x4->getCurrentTurn();
                        errorMessage = "";
                    } catch (const std::exception& e) {
                        errorMessage = "Invalid move!";
                    }
                }
            }

            ImGui::PopStyleVar();
            ImGui::PopID();
        }
        ImGui::NewLine();
    }

    ImGui::Spacing();
    ImGui::Spacing();

    // Center the control buttons
    float buttonWidth = 120.0f;
    float buttonHeight = 40.0f;
    float buttonsWidth = (buttonWidth * 2) + PADDING;
    float buttonsPadding = (contentRegion.x - buttonsWidth) * 0.5f;

    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + buttonsPadding);
    if (ImGui::Button("Reset Game", ImVec2(buttonWidth, buttonHeight))) {
        startGame(gameState.player1Name, gameState.player2Name,
                 gameState.player1Type, gameState.player2Type);
    }

    ImGui::SameLine(0, PADDING);

    if (ImGui::Button("Main Menu", ImVec2(buttonWidth, buttonHeight))) {
        showGameWindow = false;
        currentGame = NoGame;
        gameStarted = false;
    }

    // Victory check
    if (game4x4->is_win() || game4x4->isDraw()) {
        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
        ImGui::OpenPopup("Game Over");

        if (ImGui::BeginPopupModal("Game Over", nullptr,
            ImGuiWindowFlags_AlwaysAutoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoResize)) {

            std::string resultText;
            if (game4x4->is_win()) {
                resultText = (game4x4->getWinner() ? gameState.player1Name : gameState.player2Name) + " Wins!";
            } else {
                resultText = "It's a Draw!";
            }

            float windowWidth = ImGui::GetWindowSize().x;
            float textWidth = ImGui::CalcTextSize(resultText.c_str()).x;
            ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
            ImGui::Text("%s", resultText.c_str());

            ImGui::Separator();

            if (ImGui::Button("Play Again")) {
                startGame(gameState.player1Name, gameState.player2Name,
                         gameState.player1Type, gameState.player2Type);
                ImGui::CloseCurrentPopup();
            }

            ImGui::SameLine();

            if (ImGui::Button("Main Menu")) {
                showGameWindow = false;
                currentGame = NoGame;
                gameStarted = false;
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }
    }
}

void BoardGamesGUI::renderUltimateGame() {
    if (!gameUltimate || !gameStarted) return;

    // Computer player handling
    if (isCurrentPlayerComputer()) {
        static float lastMoveTime = 0.0f;
        float currentTime = ImGui::GetTime();

        if (currentTime - lastMoveTime > 0.5f) {
            std::pair<int, int> move = gameUltimate->getComputerMove();
            if (move.first != -1 && move.second != -1) {
                try {
                    if (isPlayer1Turn) {
                        gameUltimate->Player1PerformMove(move.first, move.second);
                    } else {
                        gameUltimate->Player2PerformMove(move.first, move.second);
                    }
                    isPlayer1Turn = gameUltimate->getCurrentTurn();
                    lastMoveTime = currentTime;
                } catch (const std::exception& e) {
                    errorMessage = e.what();
                }
            }
        }
    }

    ImVec2 contentRegion = ImGui::GetContentRegionAvail();
    float cellSize = 40.0f;
    float innerPadding = 3.0f;
    float outerPadding = 8.0f;

    // Game status bar
    std::string playerText = "Current Player: " +
        (isPlayer1Turn ? gameState.player1Name : gameState.player2Name);
    float textWidth = ImGui::CalcTextSize(playerText.c_str()).x;
    float textPadding = (contentRegion.x - textWidth) * 0.5f;
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + textPadding);
    ImGui::Text("%s", playerText.c_str());
    ImGui::Spacing();

    // Center the game board
    float totalBoardWidth = (cellSize * 9) + (innerPadding * 6) + (outerPadding * 2);
    float leftPadding = (contentRegion.x - totalBoardWidth) * 0.5f;

    for (int i = 0; i < 9; i++) {
        ImGui::SetCursorPosX(leftPadding);
        
        for (int j = 0; j < 9; j++) {
            if (j > 0) {
                if (j % 3 == 0) {
                    ImGui::SameLine(0, outerPadding);
                } else {
                    ImGui::SameLine(0, innerPadding);
                }
            }

            ImGui::PushID(i * 9 + j);
            
            int subGrid = (i / 3) * 3 + (j / 3);
            char subGridWinner = gameUltimate->getSubGridWinner(subGrid);

            // Style for the cell
            bool isPartOfWonGrid = (subGridWinner != ' ' && subGridWinner != 'D');
            if (isPartOfWonGrid) {
                ImGui::PushStyleColor(ImGuiCol_Button,
                    subGridWinner == 'X' ? ImVec4(0.4f, 0.2f, 0.2f, 1.0f) : ImVec4(0.2f, 0.2f, 0.4f, 1.0f));
            }

            // Highlight valid next subgrid
            int nextGrid = gameUltimate->getNextValidSubGrid();
            if (nextGrid != -1 && subGrid == nextGrid) {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.3f, 0.7f, 0.3f, 1.0f));
            }

            char symbol = gameUltimate->getSymbolAt(i, j);
            std::string buttonLabel = symbol == ' ' ? "##empty" : std::string(1, symbol);

            if (ImGui::Button(buttonLabel.c_str(), ImVec2(cellSize, cellSize))) {
                if (!isCurrentPlayerComputer()) {
                    try {
                        if (isPlayer1Turn) {
                            gameUltimate->Player1PerformMove(i, j);
                        } else {
                            gameUltimate->Player2PerformMove(i, j);
                        }
                        isPlayer1Turn = gameUltimate->getCurrentTurn();
                    } catch (const std::exception& e) {
                        errorMessage = e.what();
                    }
                }
            }

            // Draw large X or O overlay for won subgrids
            if (isPartOfWonGrid && (i % 3 == 1) && (j % 3 == 1)) {
                // Get the position of the entire subgrid instead of just the center cell
                ImVec2 subgridStart = ImGui::GetItemRectMin();
                subgridStart.x -= cellSize + innerPadding;  // Move to start of subgrid
                subgridStart.y -= cellSize + innerPadding;  // Move to top of subgrid
                
                float subGridSize = (cellSize * 3) + (innerPadding * 2);  // Total size of subgrid

                // Draw the large symbol
                ImDrawList* drawList = ImGui::GetWindowDrawList();
                if (subGridWinner == 'X') {
                    // Draw large X
                    float thickness = 3.0f;
                    ImVec2 topLeft = subgridStart;
                    ImVec2 bottomRight(topLeft.x + subGridSize, topLeft.y + subGridSize);
                    drawList->AddLine(topLeft, bottomRight, IM_COL32(255, 255, 255, 255), thickness);
                    drawList->AddLine(
                        ImVec2(topLeft.x, bottomRight.y),
                        ImVec2(bottomRight.x, topLeft.y),
                        IM_COL32(255, 255, 255, 255),
                        thickness
                    );
                } else if (subGridWinner == 'O') {
                    // Draw large O
                    float radius = subGridSize * 0.4f;
                    ImVec2 center(
                        subgridStart.x + subGridSize * 0.5f,
                        subgridStart.y + subGridSize * 0.5f
                    );
                    drawList->AddCircle(
                        center,
                        radius,
                        IM_COL32(255, 255, 255, 255),
                        0,  // num segments (0 for auto)
                        3.0f // thickness
                    );
                }
            }

            if (isPartOfWonGrid) ImGui::PopStyleColor();
            if (nextGrid != -1 && subGrid == nextGrid) ImGui::PopStyleColor();

            ImGui::PopID();
        }
        
        // Replace NewLine with cursor positioning for next row
        if (i < 8) {  // Don't need to position after last row
            float nextY = ImGui::GetCursorPosY() + innerPadding;
            if ((i + 1) % 3 == 0) {
                nextY += outerPadding;
            }
            ImGui::SetCursorPos(ImVec2(leftPadding, nextY));
        }
    }

    ImGui::Spacing();
    ImGui::Spacing();

    // Center and resize the control buttons
    float buttonWidth = 120.0f;  // Increased button width
    float buttonHeight = 40.0f;  // Increased button height
    float buttonsWidth = (buttonWidth * 2) + PADDING;  // Total width of both buttons
    float buttonsPadding = (contentRegion.x - buttonsWidth) * 0.5f;

    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + buttonsPadding);
    if (ImGui::Button("Reset Game", ImVec2(buttonWidth, buttonHeight))) {
        startGame(gameState.player1Name, gameState.player2Name,
                 gameState.player1Type, gameState.player2Type);
    }

    ImGui::SameLine(0, PADDING);

    if (ImGui::Button("Main Menu", ImVec2(buttonWidth, buttonHeight))) {
        showGameWindow = false;
        currentGame = NoGame;
        gameStarted = false;
    }

    // Victory check
    if (gameUltimate->is_win() || gameUltimate->isDraw()) {
        ImGui::OpenPopup("Game Over");
    }

    if (ImGui::BeginPopupModal("Game Over", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        std::string resultText = gameUltimate->is_win() ?
            (!isPlayer1Turn ? gameState.player1Name : gameState.player2Name) + " Wins!" :
            "It's a Draw!";

        ImGui::Text("%s", resultText.c_str());
        ImGui::Separator();

        if (ImGui::Button("Play Again")) {
            startGame(gameState.player1Name, gameState.player2Name,
                     gameState.player1Type, gameState.player2Type);
            ImGui::CloseCurrentPopup();
        }

        ImGui::SameLine();

        if (ImGui::Button("Main Menu")) {
            showGameWindow = false;
            currentGame = NoGame;
            gameStarted = false;
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}

void BoardGamesGUI::startGame(const std::string& p1Name, const std::string& p2Name,
                            BoardGame7_Wrapper::PlayerType p1Type,
                            BoardGame7_Wrapper::PlayerType p2Type) {
    gameState.player1Name = p1Name;
    gameState.player2Name = p2Name;
    gameState.player1Type = p1Type;
    gameState.player2Type = p2Type;

    if (currentGame == Game4x4) {
        game4x4 = std::make_unique<BoardGame7_Wrapper>();
        game4x4->InitializeGame(p1Name, p2Name, p1Type, p2Type);
    } else if (currentGame == GameUltimate) {
        gameUltimate = std::make_unique<UltimateTTT_Wrapper>();
        gameUltimate->InitializeGame(p1Name, p2Name,
            static_cast<UltimateTTT_Wrapper::PlayerType>(p1Type),
            static_cast<UltimateTTT_Wrapper::PlayerType>(p2Type));
    }

    gameStarted = true;
    isPlayer1Turn = true;
    selectedTokenPos = {-1, -1};
    errorMessage = "";
}

void BoardGamesGUI::cleanup() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

void BoardGamesGUI::setupStyle() {
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 5.0f;
    style.FrameRounding = 4.0f;
    style.ItemSpacing = ImVec2(12, 8);
    style.ItemInnerSpacing = ImVec2(8, 6);
    style.IndentSpacing = 25.0f;
    style.ScrollbarSize = 15.0f;
    style.ScrollbarRounding = 9.0f;
    style.GrabMinSize = 5.0f;
    style.GrabRounding = 3.0f;

    ImVec4* colors = style.Colors;
    colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.11f, 0.11f, 0.94f);
    colors[ImGuiCol_Button] = ImVec4(0.20f, 0.41f, 0.68f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.48f, 0.80f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.26f, 0.52f, 0.88f, 1.00f);
}