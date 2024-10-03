#include "Key.h"

Key::Key(olc::vi2d position) : position(position), visible(false) {}

void Key::Draw(olc::PixelGameEngine* engine, olc::Sprite* tileset)
{
    if (visible)
    {
        olc::vi2d spriteOffset = { 14, 456 };
        engine->DrawPartialSprite(position * 12, tileset, spriteOffset, { 12, 12 });
    }
}

bool Key::IsPickedUp(olc::vi2d playerPosition) const
{
    return visible && playerPosition == position;
}

bool Key::IsVisible() const
{
    return visible;
}

void Key::SetVisible(bool visibility)
{
    visible = visibility;
}
