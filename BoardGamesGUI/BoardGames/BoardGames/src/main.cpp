#include "BoardGamesGUI.h"



int main()
{
    BoardGamesGUI gui;
    if (gui.init()) {
        gui.render();
    }
    return 0;
}