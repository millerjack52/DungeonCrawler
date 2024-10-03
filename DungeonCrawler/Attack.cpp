#include "Attack.h"
#include "GameWorld.h"
#include "Enemy.h"

Attack::Attack(AttackType type, olc::vi2d gridPosition)
    : type(type), gridPosition(gridPosition)
{}

void Attack::Execute(olc::PixelGameEngine* engine, TArray<Enemy*>& targets, olc::Sprite* tileset)
{
    switch (type)
    {
    case AttackType::SINGLE:
    {
        olc::vi2d adjustedPosition = gridPosition + olc::vi2d(-1, 1);
        GameWorld::Instance->notificationManager.AddNotification("!", adjustedPosition * TILE_SIZE, 0.1f);
        break;
    }
    case AttackType::LIGHTNING:
    {
        for (int dx = -1; dx <= 1; ++dx)
        {
            for (int dy = -1; dy <= 1; ++dy)
            {
                olc::vi2d tilePos = gridPosition + olc::vi2d(dx, dy + 1);
                GameWorld::Instance->notificationManager.AddNotification("@", tilePos * TILE_SIZE, 0.1f);
            }
        }
        break;
    }
    }

    for (int i = 0; i < targets.Num(); ++i)
    {
        Enemy* target = targets.GetElement(i);
        if (target != nullptr && IsCollidingWithTarget(gridPosition, target))
        {
            if (type == AttackType::SINGLE)
            {
                target->TakeDamage(20);
                GameWorld::Instance->notificationManager.AddNotification("HIT 20 DMG", target->GetPixelPosition(), 1.0f);
            }
            else if (type == AttackType::LIGHTNING)
            {
                target->TakeDamage(10);
                GameWorld::Instance->notificationManager.AddNotification("HIT 10 DMG", target->GetPixelPosition(), 1.0f);
            }
        }
    }
}

bool Attack::IsCollidingWithTarget(olc::vi2d attackGridPosition, Enemy* target)
{
    olc::vi2d targetGridPos = target->GetGridPosition();

    if (type == AttackType::LIGHTNING)
    {
        for (int x = -1; x <= 1; ++x)
        {
            for (int y = -1; y <= 1; ++y)
            {
                olc::vi2d lightningColl = attackGridPosition + olc::vi2d(x, y);
                if (targetGridPos == lightningColl)
                {
                    return true;
                }
            }
        }
    }
    else if (targetGridPos == (attackGridPosition + olc::vi2d(-1, 0)))
    {
        return true;
    }
    return false;
}
