#include "bomb.h"

void Bomb::update(double gameTime)
{
    m_gameTime = gameTime;
    m_isXploding = false;
    if (m_gameTime > m_lastXplodeTime + 4/m_lvl)
    {
        m_isXploding = true;
        m_lastXplodeTime = m_gameTime;
    }
    
}

void Bomb::draw()
{
    if (m_lvl == 1 && !m_gameTime < m_lastXplodeTime + 0.5)
        DrawTexture(m_txtr1, m_pos.x - 150, m_pos.y - 150, WHITE);
    if (m_lvl == 1 && m_gameTime < m_lastXplodeTime + 0.5)
        DrawTexture(m_txtr1xplode, m_pos.x - 300, m_pos.y - 300, WHITE);
    if (m_lvl == 2 && !m_gameTime < m_lastXplodeTime + 0.5)
        DrawTexture(m_txtr2, m_pos.x - 200, m_pos.y - 200, WHITE);
    if (m_lvl == 2 && m_gameTime < m_lastXplodeTime + 0.5)
        DrawTexture(m_txtr2xplode, m_pos.x - 400, m_pos.y - 400, WHITE);
}