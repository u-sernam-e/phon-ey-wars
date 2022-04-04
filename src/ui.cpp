#include "ui.h"
#include "config.h"
#include "rayextended.h"
#include <string>

void Ui::update()
{
    for (Button& b : m_buttons[m_currState])
        b.update();
    switch (m_currState)
    {
        case MAINSTATE:
        {
            if (m_buttons[MAINSTATE][PLAYBUTTON].released())
                m_currState = GAMESTATE;
            if (m_buttons[MAINSTATE][MAINEXITBUTTON].released())
                m_gameShouldClose = true;
            break;
        }
        case GAMESTATE:
        {
            if (m_buttons[GAMESTATE][SLAPMACHINEBUTTON].released())
                m_game.buyAlly(1);
            if (m_buttons[GAMESTATE][BOMBBUTTON].released())
                m_game.buyAlly(3);
            if (IsKeyPressed(KEY_ESCAPE) || m_buttons[GAMESTATE][PAUSEBUTTON].released())
                m_currState = PAUSESTATE;
            bool canSlap{true};
            for (Button& b : m_buttons[GAMESTATE])
                if (b.down())
                    canSlap = false;
            if (canSlap)
                m_game.slap();
            break;
        }
        case PAUSESTATE:
        {
            if (m_buttons[PAUSESTATE][PAUSEEXITBUTTON].released())
                m_gameShouldClose = true;
            if (m_buttons[PAUSESTATE][MAINMENUBUTTON].released())
                m_currState = MAINSTATE;
            if (m_buttons[PAUSESTATE][PAUSEDBACKBUTTON].released() || IsKeyPressed(KEY_ESCAPE))
                m_currState = GAMESTATE;
            break;
        }
    }
    if (m_game.getHp() < 0)
        m_gameShouldClose = true;
}

void Ui::draw()
{
    switch (m_currState)
    {
        case MAINSTATE:
        {
            DrawTexture(m_txtrs[MAINMENUTXTR], 0, 0, WHITE);
            break;
        }
        case GAMESTATE:
        {
            DrawText((std::string{"$$$: "} + std::to_string(m_game.getMoney())).c_str(), cfg::scnW - 210, 10, 30, GREEN);
            DrawText((std::string{"HP: "} + std::to_string(m_game.getHp())).c_str(), cfg::scnW/2 - 100, 10, 30, {255, 0, 0, 255});
            break;
        }
        case PAUSESTATE:
        {
            DrawRectangle(0, 0, cfg::scnW, cfg::scnH, {0, 0, 0, 150});
            break;
        }
    }
    for (Button& b : m_buttons[m_currState])
        b.draw();
    if (!m_game.canSlap() && m_currState == GAMESTATE)
        DrawTexture(m_txtrs[CURSORSLAPTXTR], static_cast<int>(GetMousePosition().x - 250.0f), static_cast<int>(GetMousePosition().y - 250.0f), WHITE);
    else
        DrawTexture(m_txtrs[CURSORTXTR], static_cast<int>(GetMousePosition().x - 15.0f), static_cast<int>(GetMousePosition().y - 15.0f), WHITE);
}