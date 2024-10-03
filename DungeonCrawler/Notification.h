#pragma once
#include "olcPixelGameEngine.h"
#include <string>
#include <vector>

class Notification
{
public:
    Notification() : message(""), position(olc::vi2d(0, 0)), duration(0.0f), timeElapsed(0.0f) {}
    Notification(std::string message, olc::vi2d position, float duration);

    void Update(float fElapsedTime);
    bool IsExpired() const;
    void Draw(olc::PixelGameEngine* engine, olc::Sprite* tileset);
    olc::vi2d GetSpriteOffsetForChar(char c);

private:
    std::string message;
    olc::vi2d position;
    float duration;
    float timeElapsed;
};