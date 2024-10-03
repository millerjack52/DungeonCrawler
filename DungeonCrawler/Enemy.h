#pragma once
#include "Character.h"

class Enemy : public Character
{
public:
    Enemy();
    ~Enemy();

    virtual void Tick(float fElapsedTime, olc::PixelGameEngine* engine) override;
    virtual bool IsBoss() const;

private:
    int direction;
    float timeSinceDirChange;
    float timeSinceLastMove;
};
