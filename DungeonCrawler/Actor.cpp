#include "Actor.h"

Actor::Actor(olc::vi2d gridPos)
    : GridPos(gridPos)
{}

olc::vi2d Actor::GetGridPosition() const
{
    return GridPos;
}

void Actor::SetGridPosition(const olc::vi2d& position)
{
    GridPos = position;
}

olc::vi2d Actor::GetPixelPosition() const
{
    return GridPos * TILE_SIZE;
}
