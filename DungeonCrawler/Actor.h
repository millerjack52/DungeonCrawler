#pragma once
#include "olcPixelGameEngine.h"
#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 240
#define GRID_WIDTH 21
#define GRID_HEIGHT 18
#define TILE_SIZE 12 

class Actor
{
public:
    Actor(olc::vi2d gridPos = { 0, 0 });
    virtual ~Actor() = default;
    virtual void Tick(float fElapsedTime, olc::PixelGameEngine* engine) = 0;
    olc::vi2d GetGridPosition() const;
    void SetGridPosition(const olc::vi2d& position);
    olc::vi2d GetPixelPosition() const;

protected:
    olc::vi2d GridPos;

};
