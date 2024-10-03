#pragma once
#include "Character.h"
#include "Attack.h"

class Player : public Character
{
public:
    Player();
    ~Player();
    olc::vi2d GetGridPosition() const;
    virtual void Tick(float fElapsedTime, olc::PixelGameEngine* engine) override;
    void TakeDamage(int damage);
    void OnDeath();

private:
    void CheckCollisionWithEnemies();
};
