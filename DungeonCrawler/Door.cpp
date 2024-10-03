#include "Door.h"
#include "GameWorld.h"
#include "Room.h"

Door::Door(olc::vi2d position, bool isFinalDoor, Room* linkedRoom)
    : position(position), isFinalDoor(isFinalDoor), linkedRoom(linkedRoom) {}

void Door::Draw(olc::PixelGameEngine* engine, olc::Sprite* tileset)
{
    olc::vi2d spriteOffset;

    if (isFinalDoor)
    {
        spriteOffset = olc::vi2d(28, 405);
    }
    else
    {
        spriteOffset = olc::vi2d(144, 14);
    }

    engine->DrawPartialSprite(position * TILE_SIZE, tileset, spriteOffset, { TILE_SIZE, TILE_SIZE });
}

Room* Door::GetLinkedRoom() const
{
    return linkedRoom;
}

olc::vi2d Door::GetPosition() const
{
    return position;
}

bool Door::IsFinalDoor() const
{
    return isFinalDoor;
}
