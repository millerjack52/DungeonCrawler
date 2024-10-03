#include "Character.h"

Character::Character(olc::vi2d gridPos)
    : Actor(gridPos), Health(100), AnimSprite(nullptr)
{
}

Character::~Character()
{
}

void Character::SetAnimatedSprite(AnimatedSprite* sprite)
{
    AnimSprite = sprite;
}

void Character::TakeDamage(int damage)
{
    Health -= damage;
    if (Health <= 0)
    {
        Health = 0;
    }
}

int Character::GetHealth() const
{
    return Health;
}

void Character::CheckBounds(olc::vi2d& pos)
{
    if (pos.y < 0)
    {
        pos.y = 0;
    }
    if (pos.y >= GRID_HEIGHT)
    {
        pos.y = GRID_HEIGHT - 1;
    }
    if (pos.x < 0)
    {
        pos.x = 0;
    }
    if (pos.x >= GRID_WIDTH)
    {
        pos.x = GRID_WIDTH - 1;
    }
}

bool Character::IsAlive() const
{
    return Health > 0;
}
