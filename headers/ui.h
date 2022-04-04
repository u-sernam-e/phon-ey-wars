#ifndef UI
#define UI
#include "config.h"
#include "rayextended.h"
#include "button.h"
#include "gameplay.h"
#include <vector>
#include <string>

class Ui
{
public:
    enum State
    {
        MAINSTATE,
        GAMESTATE,
        PAUSESTATE,
        MAXSTATES
    };
private:
    enum Textures
    {
        CURSORTXTR,
        CURSORSLAPTXTR,
        SLAPMACHINEBUTTONTXTR,
        BOMBBUTTONTXTR,
        PLAYBUTTONTXTR,
        PAUSEBUTTONTXTR,
        EXITBUTTONTXTR,
        MAINMENUBUTTONTXTR,
        PAUSEBACKBUTTONTXTR,
        MAINMENUTXTR,
        MAXTEXTURES
    };
    std::vector<std::string> m_txtrPaths{
        "res/cursor.png",
        "res/cursorslap.png",
        "res/slapmachinebutton.png",
        "res/bombbutton.png",
        "res/playbutton.png",
        "res/pausebutton.png",
        "res/exitbutton.png",
        "res/mainmenubutton.png",
        "res/pausebackbutton.png",
        "res/mainmenu.png"
    };
    std::vector<Texture2D> m_txtrs{};
    GamePlay& m_game;
    State m_currState{MAINSTATE};
    enum MainButtons
    {
        PLAYBUTTON,
        MAINEXITBUTTON,
        MAXMAINBUTTONS
    };
    enum GameButtons
    {
        SLAPMACHINEBUTTON,
        BOMBBUTTON,
        PAUSEBUTTON,
        MAXGAMEBUTTONS
    };
    enum PauseButtons
    {
        PAUSEEXITBUTTON,
        MAINMENUBUTTON,
        PAUSEDBACKBUTTON,
        MAXPAUSEBUTTONS
    };
    std::vector<Button> m_buttons[MAXSTATES]{};
    bool m_gameShouldClose{};
public:
    Ui(GamePlay& game)
        : m_game{game}
    {
        for (auto path : m_txtrPaths)
        {
            m_txtrs.push_back(LoadTexture(path.c_str()));
        }
        m_buttons[MAINSTATE].push_back({{60, 270}, {530, 350}, m_txtrs[PLAYBUTTONTXTR], {255, 255, 255, 200}, {100, 100, 100, 255}, {255, 255, 255, 255}, "", true});
        m_buttons[MAINSTATE].push_back({{75, 620}, {500, 200}, m_txtrs[EXITBUTTONTXTR], {255, 255, 255, 200}, {100, 100, 100, 255}, {255, 255, 255, 255}, "", true});

        m_buttons[GAMESTATE].push_back({{cfg::scnW - 220, 40}, {200, 200}, m_txtrs[SLAPMACHINEBUTTONTXTR], {255, 255, 255, 200}, {100, 100, 100, 255}, {255, 255, 255, 255}, "", true});
        m_buttons[GAMESTATE].push_back({{cfg::scnW - 220, 240}, {200, 200}, m_txtrs[BOMBBUTTONTXTR], {255, 255, 255, 200}, {100, 100, 100, 255}, {255, 255, 255, 255}, "", true});
        m_buttons[GAMESTATE].push_back({{20, 20}, {100, 100}, m_txtrs[PAUSEBUTTONTXTR], {255, 255, 255, 200}, {100, 100, 100, 255}, {255, 255, 255, 255}, "", true});

        m_buttons[PAUSESTATE].push_back({{cfg::scnW/2-250, 600}, {500, 200}, m_txtrs[EXITBUTTONTXTR], {255, 255, 255, 200}, {100, 100, 100, 255}, {255, 255, 255, 255}, "", true});
        m_buttons[PAUSESTATE].push_back({{cfg::scnW/2-250, 300}, {500, 300}, m_txtrs[MAINMENUBUTTONTXTR], {255, 255, 255, 200}, {100, 100, 100, 255}, {255, 255, 255, 255}, "", true});
        m_buttons[PAUSESTATE].push_back({{20, 20}, {100, 100}, m_txtrs[PAUSEBACKBUTTONTXTR], {255, 255, 255, 200}, {100, 100, 100, 255}, {255, 255, 255, 255}, "", true});
    }
    ~Ui()
    {
        for (auto& txtr : m_txtrs)
        {
            UnloadTexture(txtr);
        }
    }

    void update();
    void draw();
    State getState() { return m_currState; }
    bool closeGame() {return m_gameShouldClose; }
};

#endif