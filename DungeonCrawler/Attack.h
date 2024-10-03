#pragma once
#include "olcPixelGameEngine.h"
#include "TArray.h"
#include "Enemy.h"

enum class AttackType
{
    SINGLE,
    LIGHTNING
};

class Attack
{
public:
    Attack(AttackType type, olc::vi2d gridPosition);
    void Execute(olc::PixelGameEngine* engine, TArray<Enemy*>& targets, olc::Sprite* tileset);

private:
    bool IsCollidingWithTarget(olc::vi2d attackGridPosition, Enemy* target);

    AttackType type;
    olc::vi2d gridPosition;
};
