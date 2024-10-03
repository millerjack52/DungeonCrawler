#include "Notification.h"

Notification::Notification(std::string message, olc::vi2d position, float duration)
    : message(message), position(position), duration(duration), timeElapsed(0.0f)
{}

void Notification::Update(float fElapsedTime)
{
    timeElapsed += fElapsedTime;
}

bool Notification::IsExpired() const
{
    return timeElapsed >= duration;
}

void Notification::Draw(olc::PixelGameEngine* engine, olc::Sprite* tileset)
{
    if (!IsExpired())
    {
        olc::vi2d drawPos = position;
        drawPos.y -= 12;

        for (const char& c : message)
        {
            if (c == ' ')
            {
                drawPos.x += 13;
                continue;
            }

            olc::vi2d spriteOffset = GetSpriteOffsetForChar(c);
            if (spriteOffset != olc::vi2d(0, 0))
            {
                engine->DrawPartialSprite(drawPos, tileset, spriteOffset, { 12, 12 });
            }
            drawPos.x += 13;
        }
    }
}

olc::vi2d Notification::GetSpriteOffsetForChar(char c)
{
    if (c >= 'A' && c <= 'T')
    {
        int index = c - 'A';
        return olc::vi2d(1 + index * 13, 573);
    }
    else if (c >= 'U' && c <= 'Z')
    {
        int index = c - 'U';
        return olc::vi2d(1 + index * 13, 586);
    }
    else if (c >= '1' && c <= '5')
    {
        int index = c - '1';
        return olc::vi2d(261 + index * 13, 573);
    }
    else if ((c >= '6' && c <= '9') || c == '0')
    {
        int index;
        if (c == '0')
        {
            index = 4;
        }
        else
        {
            index = c - '6';
        }
        return olc::vi2d(261 + index * 13, 586);
    }
    else if (c == '!') {
        return olc::vi2d(339, 274);
    }
    else if (c == '@') {
        return olc::vi2d(339, 495);
    }
    return olc::vi2d(0, 0);
}

