#ifndef SLAPMACHINE
#define SLAPMACHINE
#include "rayextended.h"

class SlapMachine
{
private:
    const Texture2D& m_txtr1{};
    const Texture2D& m_txtr2{};
    int m_lvl{ 1 };
    Vector2 m_pos{};
    float m_rot{};
    long long m_lastDamagedTimeMs{};
public:
    SlapMachine( Vector2 pos, const Texture2D& txtr1, const Texture2D& txtr2 )
        : m_pos{pos}
        , m_txtr1{txtr1}
        , m_txtr2{txtr2}
    {}

    void update();
    void draw();
    int getDamage() { return 1; }
    void lvlUp() { if (m_lvl == 1) ++m_lvl; }
    bool doDamage();
    bool canDoDamage();
    Vector2 getPos() { return m_pos; }
    int getLvl() { return m_lvl; }
};

#endif