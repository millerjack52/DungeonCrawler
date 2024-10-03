#pragma once
#include "Enemy.h"
#include "Player.h"

class Boss : public Enemy
{
public:
    Boss();
    ~Boss();

    void Tick(float fElapsedTime, olc::PixelGameEngine* engine) override;
    void AttackPlayer(Player* player);
    bool IsBoss() const override;

private:
    int direction;
    float timeSinceDirChange;
    float timeSinceLastMove;
};
