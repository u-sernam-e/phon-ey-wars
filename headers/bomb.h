#ifndef BOMB
#define BOMB
#include "rayextended.h"

class Bomb
{
private:
    const Texture2D& m_txtr1{};
    const Texture2D& m_txtr1xplode{};
    const Texture2D& m_txtr2{};
    const Texture2D& m_txtr2xplode{};
    int m_lvl{ 1 };
    Vector2 m_pos{};
    bool m_isXploding{};
    double m_lastXplodeTime{};
    double m_gameTime{};
public:
    Bomb(const Texture2D& t1, const Texture2D& tx1, const Texture2D& t2, const Texture2D& tx2, Vector2 pos)
        : m_txtr1{t1}
        , m_txtr1xplode{tx1}
        , m_txtr2{t2}
        , m_txtr2xplode{tx2}
        , m_pos{pos}
    {}
    void update(double gameTime);
    void draw();
    bool isXploding() { return m_isXploding; }
    int getLvl() { return m_lvl; }
    Vector2 getPos() { return m_pos; }
    int getDamage() { return m_lvl * 7; }
    void lvlUp() { m_lvl = 2; }
};

#endif