#pragma once
#include "olcPixelGameEngine.h"

enum class EAnimationType { STILL, LOOP_ONCE, LOOP_FOREVER };

struct FAnimSequence
{
    olc::vi2d FirstFrameOffset;
    olc::vi2d TileSize;
    int FrameCount;
    float Duration;
};

class AnimatedSprite
{
public:
    AnimatedSprite(olc::Sprite* sprite, FAnimSequence animSeq, EAnimationType animType);
    void DrawAt(float fElapsedTime, olc::vi2d InScreenPosition);

private:
    olc::Sprite* SpriteSheet;
    EAnimationType AnimationType;
    FAnimSequence AnimSequence;
    float ElapsedTime;
};
