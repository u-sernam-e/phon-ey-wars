#ifndef SCAMMER
#define SCAMMER
#include "allybase.h"

class Scammer : AllyBase
{
public:
    bool isScammer() override;
    bool checkCollision(GamePlay::EnemyHand e) override;
    void update() override;
    void draw() override;
    int getPrice() override;
    int getDamage() override;
};

#endif