#include "Boss.h"

Boss::Boss()
    : Enemy(), direction(0), timeSinceDirChange(0.0f), timeSinceLastMove(0.0f)
{
    GridPos = olc::vi2d(rand() % GRID_WIDTH, rand() % GRID_HEIGHT);
    Health = 200;
}

Boss::~Boss()
{
}

void Boss::Tick(float fElapsedTime, olc::PixelGameEngine* engine)
{
    timeSinceDirChange += fElapsedTime;
    timeSinceLastMove += fElapsedTime;

    if (timeSinceDirChange >= 1.0f)
    {
        direction = rand() % 4;
        timeSinceDirChange = 0.0f;
    }

    if (timeSinceLastMove >= 0.2f)
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

void Boss::AttackPlayer(Player* player)
{
    player->TakeDamage(20);
}

bool Boss::IsBoss() const
{
    return true;
}
