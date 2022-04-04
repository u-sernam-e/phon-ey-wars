#ifndef BUTTON
#define BUTTON
#include "rayextended.h"
#include <string>

class Button
{
private:
    enum State
    {
        UP,
        DOWN,
        HOVER,
        PRESSED,
        RELEASED,
        MAXBUTTONSTATE
    };
    Vector2 m_pos{};
    Vector2 m_size{};
    Color m_upTint{};
    Color m_hoverTint{};
    Color m_downTint{};
    Texture2D m_txtr{};
    std::string m_txt{};
    bool m_hasTxtr{};
    State m_state{};
    int test{};
public:
    Button(Vector2 pos, Vector2 size, const Texture2D& texture, Color upTint, Color downTint, Color hoverTint, std::string text, bool isTxtrd)
        : m_pos{pos}
        , m_size{size}
        , m_upTint{upTint}
        , m_downTint{downTint}
        , m_hoverTint{hoverTint}
        , m_txt{text}
        , m_hasTxtr{isTxtrd}
        , m_txtr{texture}
    {}

    void update();
    void draw();

    bool down();
    bool pressed();
    bool released();
    bool hover();
};

#endif