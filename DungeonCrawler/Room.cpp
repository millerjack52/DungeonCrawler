#include "Room.h"
#include "Door.h"
#include "Key.h"
#include "olcPixelGameEngine.h"
#include "GameWorld.h"

Room::Room(const std::string& floorType)
    : floorType(floorType), key(olc::vi2d(0, 0)), keyPlaced(false), keyCollected(false)
{}

void Room::AddDoor(Door* door)
{
    doors.push_back(door);
}

void Room::DrawRoom(olc::PixelGameEngine* engine, olc::Sprite* tileset)
{
    olc::vi2d spriteOffset;
    if (floorType == "brick")
        spriteOffset = olc::vi2d(118, 40);
    else if (floorType == "stone")
        spriteOffset = olc::vi2d(15, 40);
    else if (floorType == "wood")
        spriteOffset = olc::vi2d(15, 2);

    for (int x = 0; x < GRID_WIDTH; x++)
    {
        for (int y = 0; y < GRID_HEIGHT; y++)
        {
            olc::vi2d drawPosition = olc::vi2d(x, y) * TILE_SIZE;
            engine->DrawPartialSprite(drawPosition, tileset, spriteOffset, { TILE_SIZE, TILE_SIZE });
        }
    }
    for (Door* door : doors)
    {
        door->Draw(engine, tileset);
    }
    key.Draw(engine, tileset);
}

void Room::PlaceKey(olc::vi2d keyPosition)
{
    key = Key(keyPosition);
    key.SetVisible(true);
    keyPlaced = true;
}

bool Room::IsKeyPickedUp(olc::vi2d playerPosition)
{
    if (key.IsPickedUp(playerPosition))
    {
        keyCollected = true;
        return true;
    }
    return false;
}

bool Room::IsPlayerAtFinalDoor(olc::vi2d playerPos)
{
    for (int i = 0; i < doors.size(); ++i)
    {
        Door* door = doors[i];
        if (door->GetPosition() == playerPos && door->IsFinalDoor())
        {
            return true;
        }
    }
    return false;
}


bool Room::IsPlayerAtAnyDoor(olc::vi2d playerPos)
{
    for (int i = 0; i < doors.size(); ++i)
    {
        Door* door = doors[i];
        if (door->GetPosition() == playerPos)
        {
            return true;
        }
    }
    return false;
}

Door* Room::GetDoorAt(olc::vi2d position)
{
    for (int i = 0; i < doors.size(); ++i)
    {
        Door* door = doors[i];
        if (door->GetPosition() == position)
        {
            return door;
        }
    }
    return nullptr;
}


bool Room::IsKeyPlaced() const
{
    return keyPlaced;
}

bool Room::IsKeyCollected() const
{
    return keyCollected;
}

void Room::SetKeyCollected(bool collected)
{
    keyCollected = collected;
}
