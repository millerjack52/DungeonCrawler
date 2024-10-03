#include "Enemy.h"

Enemy::Enemy()
    : Character(), direction(0), timeSinceDirChange(0.0f), timeSinceLastMove(0.0f)
{
    GridPos = olc::vi2d(rand() % GRID_WIDTH, rand() % GRID_HEIGHT);
    direction = rand() % 4;
}

Enemy::~Enemy()
{
}

void Enemy::Tick(float fElapsedTime, olc::PixelGameEngine* engine)
{
    timeSinceDirChange += fElapsedTime;
    timeSinceLastMove += fElapsedTime;

    if (timeSinceDirChange >= 1.0f)
    {
        direction = rand() % 4;
        timeSinceDirChange = 0.0f;
    }

    if (timeSinceLastMove >= 1.5f)
    {
        switch (direction)
        {
        case 0:
            GridPos.y += 1;
            break;
        case 1:
            GridPos.y -= 1;
            break;
        case 2:
            GridPos.x += 1;
            break;
        case 3:
            GridPos.x -= 1;
            break;
        }

        CheckBounds(GridPos);
        timeSinceLastMove = 0.0f;
    }

    if (AnimSprite)
    {
        AnimSprite->DrawAt(fElapsedTime, GetPixelPosition());
    }
}

bool Enemy::IsBoss() const
{
    return false;
};
