#include "config.h"
#include "ui.h"
#include "gameplay.h"
#include "rayextended.h"


int main(void)
{
    SetRandomSeed(getSystemTimeMil());
    InitWindow(cfg::scnW, cfg::scnH, "game!");
    
    HideCursor();
    GamePlay game{};
    Ui ui{ game };

    while (!ui.closeGame() && !(WindowShouldClose() && !IsKeyPressed(KEY_ESCAPE)))
    {
            if (ui.getState() == Ui::GAMESTATE)
                game.update();
            ui.update();

        BeginDrawing();

            ClearBackground(WHITE);

            game.draw();
            ui.draw();

        EndDrawing();
    }

    
    CloseWindow();

    return 0;
}