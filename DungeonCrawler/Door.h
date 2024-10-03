#pragma once
#include "olcPixelGameEngine.h"

class Room;

class Door
{
public:
    Door(olc::vi2d position, bool isFinalDoor, Room* linkedRoom = nullptr);
    void Draw(olc::PixelGameEngine* engine, olc::Sprite* tileset);
    olc::vi2d GetPosition() const;
    bool IsFinalDoor() const;
    Room* GetLinkedRoom() const;

private:
    olc::vi2d position;
    bool isFinalDoor;
    Room* linkedRoom;
};
