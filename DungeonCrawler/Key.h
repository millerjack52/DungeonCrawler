#pragma once
#include "olcPixelGameEngine.h"

class Key
{
public:
    Key(olc::vi2d position);

    void Draw(olc::PixelGameEngine* engine, olc::Sprite* tileset);
    bool IsPickedUp(olc::vi2d playerPosition) const;
    bool IsVisible() const;
    void SetVisible(bool visibility);

private:
    olc::vi2d position;
    bool visible;
};
