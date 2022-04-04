#include "gameplay.h"
#include "config.h"
#include "timer.h"
#include "rayextended.h"
#include "slapmachine.h"
#include <cmath>
#include <string>

int GamePlay::getEnemyMaxHp(GamePlay::EnemyType t)
{
    switch (t)
    {
    case LVL1ENEMYTYPE:
        return 1;
    case LVL2ENEMYTYPE:
        return 5;
    case LVL3ENEMYTYPE:
        return 10;
    case LVL4ENEMYTYPE:
        return 30;
    case LVL5ENEMYTYPE:
        return 100;
    default:
        return 1;
    }
}

int GamePlay::getEnemySpeed(GamePlay::EnemyType t)
{
    switch (t)
    {
    case LVL1ENEMYTYPE:
        return 2;
    case LVL2ENEMYTYPE:
        return 3;
    case LVL3ENEMYTYPE:
        return 5;
    case LVL4ENEMYTYPE:
        return 6;
    case LVL5ENEMYTYPE:
        return 1;
    default:
        return 1;
    }
}

Vector2 GamePlay::getEnemyPoint(GamePlay::EnemyHand& e, int quad) // I LOVE MATH HAHAHHAHAHAHAH
{
    switch(quad)
    {
        case 1:
            return {(std::cosf(DEG2RAD * e.angle) * (e.distance)) + std::cosf(DEG2RAD * e.angle) * 2000 + cfg::scnW/2, (std::sinf(DEG2RAD * e.angle) * (e.distance)) + std::sinf(DEG2RAD * e.angle) * 2000 + cfg::scnH};
        case 2:
            return {(std::cosf(DEG2RAD * e.angle) * (e.distance)) + std::cosf(DEG2RAD * (e.angle-90)) * 200 + std::cosf(DEG2RAD * e.angle) * 2000 + cfg::scnW/2, (std::sinf(DEG2RAD * e.angle) * (e.distance)) + std::sinf(DEG2RAD * (e.angle-90)) * 200 + std::sinf(DEG2RAD * e.angle) * 2000 + cfg::scnH};
        case 3:
            return {(std::cosf(DEG2RAD * e.angle) * (e.distance)) + std::cosf(DEG2RAD * (e.angle-90)) * 200 + cfg::scnW/2, (std::sinf(DEG2RAD * e.angle) * (e.distance)) + std::sinf(DEG2RAD * (e.angle-90)) * 200 + cfg::scnH};
        case 4:
            return {(std::cosf(DEG2RAD * e.angle) * (e.distance)) + cfg::scnW/2, (std::sinf(DEG2RAD * e.angle) * (e.distance)) + cfg::scnH};
        default:
            return {0, 0};
    }
}

bool GamePlay::collide(GamePlay::EnemyHand& e, SlapMachine& a)
{
    Vector2 enLines[3][2] {
        {getEnemyPoint(e, 1), getEnemyPoint(e, 4)},
        {getEnemyPoint(e, 4), getEnemyPoint(e, 3)},
        {getEnemyPoint(e, 3), getEnemyPoint(e, 2)}
    };
    float width{300};
    float offset{0};
    if (a.getLvl() == 2)
    {
        width = 500;
        offset = -100;
    }
    Vector2 alLines[4][2] {
        {a.getPos() + Vector2{width/2 + offset, offset}, a.getPos() + Vector2{width + offset, width/2 + offset}},
        {a.getPos() + Vector2{width + offset, width/2 + offset}, a.getPos() + Vector2{width/2 + offset, width + offset}},
        {a.getPos() + Vector2{width/2 + offset, width + offset}, a.getPos() + Vector2{offset, width/2 + offset}},
        {a.getPos() + Vector2{offset, width/2 + offset}, a.getPos() + Vector2{width/2 + offset, offset}},
    };
    if (a.canDoDamage())
    {
        for (auto& enL : enLines)
        {
            for (auto& alL : alLines)
            {
                if (CheckCollisionLines(enL[0], enL[1], alL[0], alL[1], nullptr))
                {
                    a.doDamage();
                    return true;
                }
            }
        }
    }
    return false;
}

bool GamePlay::collide(GamePlay::EnemyHand& e, Bomb& a)
{
    Vector2 enLines[3][2] {
        {getEnemyPoint(e, 1), getEnemyPoint(e, 4)},
        {getEnemyPoint(e, 4), getEnemyPoint(e, 3)},
        {getEnemyPoint(e, 3), getEnemyPoint(e, 2)}
    };
    float width{150};
    if (a.getLvl() == 2)
        width = 200;
    Vector2 alLines[4][2] {
        {a.getPos() + Vector2{0, -width}, a.getPos() + Vector2{width, 0}},
        {a.getPos() + Vector2{width, 0}, a.getPos() + Vector2{0, width}},
        {a.getPos() + Vector2{0, width}, a.getPos() + Vector2{-width, 0}},
        {a.getPos() + Vector2{-width, 0}, a.getPos() + Vector2{0, -width}},
    };
    if (a.isXploding())
    {
        for (auto& enL : enLines)
        {
            for (auto& alL : alLines)
            {
                if (CheckCollisionLines(enL[0], enL[1], alL[0], alL[1], nullptr))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool GamePlay::collideCursor(EnemyHand& e)
{
    Vector2 enLines[3][2] {
        {getEnemyPoint(e, 1), getEnemyPoint(e, 4)},
        {getEnemyPoint(e, 4), getEnemyPoint(e, 3)},
        {getEnemyPoint(e, 3), getEnemyPoint(e, 2)}
    };
    Vector2 alLines[4][2] {
        {GetMousePosition() + Vector2{0, -250}, GetMousePosition() + Vector2{250, 0}},
        {GetMousePosition() + Vector2{250, 0}, GetMousePosition() + Vector2{0, 250}},
        {GetMousePosition() + Vector2{0, 250}, GetMousePosition() + Vector2{-250, 0}},
        {GetMousePosition() + Vector2{-250 + 0}, GetMousePosition() + Vector2{0, -250}}
    };
    for (auto& enL : enLines)
    {
        for (auto& alL : alLines)
        {
            if (CheckCollisionLines(enL[0], enL[1], alL[0], alL[1], nullptr))
                return true;
        }
    }
    return false;
}

void GamePlay::setDifficulty()
{
    if (m_gameTime > 3600)
        m_difficulty = 9;
    else if (m_gameTime > 1800)
        m_difficulty = 8;
    else if (m_gameTime > 900)
        m_difficulty = 7;
    else if (m_gameTime > 600)
        m_difficulty = 6;
    else if (m_gameTime > 300)
        m_difficulty = 5;
    else if (m_gameTime > 120)
        m_difficulty = 4;
    else if (m_gameTime > 60)
        m_difficulty = 3;
    else if (m_gameTime > 30)
        m_difficulty = 2;
    else if (m_gameTime > 10)
        m_difficulty = 1;
    else
        m_difficulty = 0;
}

void GamePlay::spawnEnemy(EnemyType e)
{
    m_enemies.push_back({e, getEnemyMaxHp(e), startingEnemyDistance, static_cast<float>(GetRandomValue(220, 360))});
    
    m_nextSpawn[e] += m_enemydelay[e][m_difficulty];
}

void GamePlay::spawnEnemies()
{
    for (int et{}; et < MAXENEMYTYPES; ++et)
    {
        if (m_gameTime >= m_nextSpawn[et])
            spawnEnemy(static_cast<EnemyType>(et));
    }
}

void GamePlay::update()
{
    m_gameTime += GetFrameTime();
    setDifficulty();
    spawnEnemies();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && m_dragMode == 1)
    {
        m_slapMachines.push_back({GetMousePosition() - Vector2{150, 150}, m_txtrs[SLAPMACHINE1TXTR], m_txtrs[SLAPMACHINE2TXTR]});
        m_dragMode = 0;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && m_dragMode == 3)
    {
        m_bombs.push_back({m_txtrs[BOMB1TXTR], m_txtrs[BOMBX1TXTR], m_txtrs[BOMB2TXTR], m_txtrs[BOMBX2TXTR], GetMousePosition()});
        m_dragMode = 0;
    }

    int currEnemyNum{};
    for (auto& en : m_enemies)
    {
        en.distance -= getEnemySpeed(en.type) * 100 * GetFrameTime();
        if (en.distance < 50)
        {
            m_enemies.erase(m_enemies.begin() + currEnemyNum);
            m_playerHp -= getEnemyMaxHp(en.type);
            --currEnemyNum;
        }
        if (en.hp <= 0)
        {
            m_money += getEnemyMaxHp(en.type);
            m_enemies.erase(m_enemies.begin() + currEnemyNum);
            --currEnemyNum;
        }
        ++currEnemyNum;
    }
    
    
    for (SlapMachine& a : m_slapMachines)
    {
        a.update();
        for (auto& en : m_enemies)
        {
            if (collide(en, a))
                en.hp -= a.getDamage();
        }
    }

    for (Bomb& a : m_bombs)
    {
        a.update(m_gameTime);
        for (auto& en : m_enemies)
        {
            if (collide(en, a))
                en.hp -= a.getDamage();
        }
    }
}

void GamePlay::draw()
{
    DrawTexture(m_txtrs[GAMEBACKGROUNDTXTR], 0, 0, WHITE);
    DrawTexture(m_txtrs[PHONETXTR], cfg::scnW/2 - 100, cfg::scnH - 100, WHITE);
    for (auto& en : m_enemies)
    {
        DrawTextureEx(m_txtrs[en.type] // implicit type conversion btween enums
            , {(std::cosf(DEG2RAD * en.angle) * (2000 + en.distance)) + cfg::scnW/2, (std::sinf(DEG2RAD * en.angle) * (2000 + en.distance)) + cfg::scnH}
            , en.angle + 180, 1.0f, WHITE);
    }
    for (SlapMachine& a : m_slapMachines)
    {
        a.draw();
    }
    for (Bomb& a : m_bombs)
    {
        a.draw();
    }
    if (m_dragMode == 1)
        SlapMachine{GetMousePosition() - Vector2{150, 150}, m_txtrs[SLAPMACHINE1TXTR], m_txtrs[SLAPMACHINE2TXTR]}.draw();
    if (m_dragMode == 3)
        DrawTexture(m_txtrs[BOMB1TXTR], GetMousePosition().x - 150, GetMousePosition().y - 150, WHITE);
}

void GamePlay::buyAlly( int mode )
{
    if (mode == 0)
    {
        m_dragMode = 0;
        return;
    }
    if (m_inBuyMode[mode])
    {
        if (m_money >= m_allyPrice[mode][0])
        {
            m_money -= m_allyPrice[mode][0];
            m_dragMode = mode;
            m_inBuyMode[mode] = false;
        }
    }
    else
    {
        if (m_money >= m_allyPrice[mode][1])
        {
            m_money -= m_allyPrice[mode][1];
            if (mode == 1)
                m_slapMachines[m_slapMachines.size() - 1].lvlUp();
            if (mode == 3)
                m_bombs[m_bombs.size() - 1].lvlUp();
            m_inBuyMode[mode] = true;
        }
    }
}

bool GamePlay::canSlap()
{
    return m_lastTimeSlapped + 0.5 <= m_gameTime;
}

void GamePlay::slap()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && m_dragMode == 0 && m_lastTimeSlapped + 0.5 <= m_gameTime)
    {
        for (auto& en : m_enemies)
        {
            if (collideCursor(en))
                en.hp -= 3;
        }
        m_lastTimeSlapped = m_gameTime;
    }
}
