#pragma once
#include "olcPixelGameEngine.h"
#include "Door.h"
#include "Key.h"
#include <vector>

class Room
{
public:
    Room(const std::string& floorType);

    void AddDoor(Door* door);
    void DrawRoom(olc::PixelGameEngine* engine, olc::Sprite* tileset);
    bool IsPlayerAtFinalDoor(olc::vi2d playerPos);
    bool IsPlayerAtAnyDoor(olc::vi2d playerPos);
    Door* GetDoorAt(olc::vi2d position);

    void PlaceKey(olc::vi2d keyPosition);
    bool IsKeyPickedUp(olc::vi2d playerPosition);

    bool IsKeyPlaced() const;
    bool IsKeyCollected() const;
    void SetKeyCollected(bool collected);

private:
    std::vector<Door*> doors;
    std::string floorType;
    Key key;
    bool keyPlaced;
    bool keyCollected;
};
