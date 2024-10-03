#pragma once
#include "Actor.h"
#include "AnimatedSprite.h"

class Character : public Actor
{
public:
    Character(olc::vi2d gridPos = { 0, 0 });
    virtual ~Character();

    void SetAnimatedSprite(AnimatedSprite* sprite);
    virtual void Tick(float fElapsedTime, olc::PixelGameEngine* engine) override = 0;

    void CheckBounds(olc::vi2d& pos);
    int GetHealth() const;
    void TakeDamage(int damage);
    bool IsAlive() const;

protected:
    int Health;
    AnimatedSprite* AnimSprite;
};
