#ifndef GAMEPLAY
#define GAMEPLAY
#include "rayextended.h"
#include "slapmachine.h"
#include "bomb.h"
#include "timer.h"
#include <vector>
#include <string>

class GamePlay
{
public:
    enum EnemyType
    {
        LVL1ENEMYTYPE,
        LVL2ENEMYTYPE,
        LVL3ENEMYTYPE,
        LVL4ENEMYTYPE,
        LVL5ENEMYTYPE,
        MAXENEMYTYPES
    };
    struct EnemyHand
    {
        EnemyType type;
        int hp;
        float distance;
        float angle;
    };
private:
    static constexpr double m_enemydelay[5][10]{
        { 0.5 , 0.2 , 0.1 , 0.1, 0.1, 0.1 , 0.1 , 0.1, 0.1, 0.1 },
        { 30  , 0   , 2   , 1.5 , 1   , 0.5 , 0.4 , 0.3 , 0.2 , 0.05 },
        { 60  , 0   , 0   , 2   , 1   , 0.9 , 0.8 , 0.5 , 0.1 , 0.05 },
        { 600 , 0   , 0   , 0   , 0   , 0   , 2   , 1   , 0.5 , 0.1  },
        { 300 , 0   , 0   , 0   , 0   , 300 , 60  , 50  , 10  , 3    }
    };
    static constexpr int m_allyPrice[5][2]{
        { 0 , 0  },
        { 20, 100 },
        { 80, 400 },
        { 60, 300 },
        { 30, 150 }
    };
    static constexpr float startingEnemyDistance{ 1100.0f };
    std::vector<EnemyHand> m_enemies{};
    enum Textures
    {
        ENEMYLVL1TXTR,
        ENEMYLVL2TXTR,
        ENEMYLVL3TXTR,
        ENEMYLVL4TXTR,
        ENEMYLVL5TXTR,
        SLAPMACHINE1TXTR,
        SLAPMACHINE2TXTR,
        BOMB1TXTR,
        BOMB2TXTR,
        BOMBX1TXTR,
        BOMBX2TXTR,
        PHONETXTR,
        GAMEBACKGROUNDTXTR,
        MAXTEXTURES
    };
    std::vector<std::string> m_txtrPaths{
        "res/enemylvl1.png",
        "res/enemylvl2.png",
        "res/enemylvl3.png",
        "res/enemylvl4.png",
        "res/enemylvl5.png",
        "res/slapmachine1.png",
        "res/slapmachine2.png",
        "res/bomb1.png",
        "res/bomb2.png",
        "res/bombx1.png",
        "res/bombx2.png",
        "res/phone.png",
        "res/gamebackground.png"
    };
    std::vector<Texture2D> m_txtrs{};
    int m_playerHp{ 500 };
    int m_money{10};
    int getEnemyMaxHp(EnemyType t);
    int getEnemySpeed(EnemyType t);
    Vector2 getEnemyPoint(EnemyHand& e, int quad); // 1 2 3 or 4
    bool collide(EnemyHand& e, SlapMachine& a);
    bool collide(EnemyHand& e, Bomb& a);
    bool collideCursor(EnemyHand& e);
    std::vector<SlapMachine> m_slapMachines{};
    std::vector<Bomb> m_bombs{};
    int m_dragMode{};
    double m_gameTime{};
    double m_nextSpawn[5]{};
    int m_difficulty{};
    void spawnEnemy(EnemyType e);
    void spawnEnemies();
    void setDifficulty();
    std::vector<bool> m_inBuyMode{0, 1, 1, 1, 1};
    double m_lastTimeSlapped{};
public:
    GamePlay()
    {
        for (auto path : m_txtrPaths)
        {
            m_txtrs.push_back(LoadTexture(path.c_str()));
        }
        for (int i{}; i < 5; ++i)
        {
            m_nextSpawn[i] = m_enemydelay[i][0];
        }
    }
    ~GamePlay()
    {
        for (auto& txtr : m_txtrs)
        {
            UnloadTexture(txtr);
        }
    }
    void update();
    void draw();
    int getHp(){ return m_playerHp; }
    int getMoney(){ return m_money; }
    void buyAlly( int mode ); // 0=none, 1=slapmachine, 2=gun, 3=bomb, 4=scammer
    void slap();
    bool canSlap();
};

#endif