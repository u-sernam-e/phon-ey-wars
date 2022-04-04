#ifndef GUN
#define GUN
#include "rayextended.h"

class Gun
{
private:
    const Texture2D& m_txtr1{};
    const Texture2D& m_txtr2{};
    int m_lvl{ 1 };
    Vector2 m_pos{};
    float m_rot{};
public:
    void update();
    void draw();
    int getPrice();
    int getDamage();
};

#endif