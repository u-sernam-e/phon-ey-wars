#include "slapmachine.h"
#include "timer.h"
#include <cmath>
#include <iostream>
#include <string>

void SlapMachine::update()
{
    m_rot -= 300 * m_lvl * GetFrameTime();
    if (IsKeyPressed(KEY_L))
        m_lvl = 2;
}

void SlapMachine::draw()
{
    Color tint{255, 255, 255, 180};
    if (canDoDamage())
        tint = WHITE;
    if (m_lvl == 1)
        DrawTextureEx(m_txtr1, {std::cosf(DEG2RAD * (m_rot + 225)) * 215 + 150 + m_pos.x, std::sinf(DEG2RAD * (m_rot + 225)) * 215 + 150 + m_pos.y}, m_rot, 1.0f, tint);
    else
        DrawTextureEx(m_txtr2, {std::cosf(DEG2RAD * (m_rot + 225)) * 355 + 150 + m_pos.x, std::sinf(DEG2RAD * (m_rot + 225)) * 355 + 150 + m_pos.y}, m_rot, 1.0f, tint);
}

bool SlapMachine::doDamage()
{
    if (getMilTimeSince(m_lastDamagedTimeMs) > 250 / m_lvl)
    {
        m_lastDamagedTimeMs = getSystemTimeMil();
        return true;
    }
    return false;
}

bool SlapMachine::canDoDamage()
{
    return getMilTimeSince(m_lastDamagedTimeMs) > 250 / m_lvl;
}