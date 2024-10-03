#include "Player.h"
#include "Attack.h"
#include "GameWorld.h"
#include "Enemy.h"
#include "Boss.h"

Player::Player() : Character(olc::vi2d(8, 8))
{
}

Player::~Player()
{
}

void Player::Tick(float fElapsedTime, olc::PixelGameEngine* engine)
{
    if (engine->GetKey(olc::Key::W).bPressed)
    {
        GridPos.y -= 1;
        CheckBounds(GridPos);
    }

    if (engine->GetKey(olc::Key::S).bPressed)
    {
        GridPos.y += 1;
        CheckBounds(GridPos);
    }

    if (engine->GetKey(olc::Key::A).bPressed)
    {
        GridPos.x -= 1;
        CheckBounds(GridPos);
    }

    if (engine->GetKey(olc::Key::D).bPressed)
    {
        GridPos.x += 1;
        CheckBounds(GridPos);
    }

    if (AnimSprite)
    {
        AnimSprite->DrawAt(fElapsedTime, GetPixelPosition());
    }

    if (engine->GetKey(olc::Key::SPACE).bPressed)
    {
        Attack attack(AttackType::SINGLE, GridPos);
        attack.Execute(engine, GameWorld::Instance->GetEnemies(), GameWorld::Instance->Tileset);
    }

    if (engine->GetKey(olc::Key::SHIFT).bPressed)
    {
        Attack attack(AttackType::LIGHTNING, GridPos);
        attack.Execute(engine, GameWorld::Instance->GetEnemies(), GameWorld::Instance->Tileset);
    }

    CheckCollisionWithEnemies();
}

void Player::CheckCollisionWithEnemies()
{
    for (int i = 0; i < GameWorld::Instance->GetEnemies().Num(); ++i)
    {
        Enemy* enemy = GameWorld::Instance->GetEnemies().GetElement(i);
        if (enemy->GetGridPosition() == GridPos)
        {
            if (enemy->IsBoss())
            {
                GridPos.y -= (rand() % 3) + 1;
                GridPos.x -= (rand() % 3) + 1;
                TakeDamage(20);
            }
            else
            {
                GridPos.y -= (rand() % 3) + 1;
                GridPos.x -= (rand() % 3) + 1;
                TakeDamage(10);
            }

            GameWorld::Instance->notificationManager.AddNotification("PLAYER DAMAGED", olc::vi2d(50, 70), 2.0f);
            CheckBounds(GridPos);
        }
    }
}

olc::vi2d Player::GetGridPosition() const
{
    return GridPos;
}

void Player::TakeDamage(int damage)
{
    Health -= damage;
    if (Health <= 0)
    {
        Health = 0;
        OnDeath();
    }
}

void Player::OnDeath()
{
    GameWorld::Instance->gameOver = true;
    GameWorld::Instance->notificationManager.AddNotification("YOU DIED GAME OVER", olc::vi2d(50, 50), 3.0f);
}
