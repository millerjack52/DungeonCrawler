#include "AnimatedSprite.h"
#include "GameWorld.h"
#include <cmath>

AnimatedSprite::AnimatedSprite(olc::Sprite* sprite, FAnimSequence animSeq, EAnimationType animType)
    : SpriteSheet(sprite), AnimSequence(animSeq), AnimationType(animType), ElapsedTime(0.0f)
{
}

void AnimatedSprite::DrawAt(float fElapsedTime, olc::vi2d InScreenPosition)
{
    ElapsedTime += fElapsedTime;

    float timePerFrame = AnimSequence.Duration / AnimSequence.FrameCount;
    int currentFrame = static_cast<int>(ElapsedTime / timePerFrame);

    if (AnimationType == EAnimationType::STILL) {
        currentFrame = 0;
    }
    else if (AnimationType == EAnimationType::LOOP_ONCE) {
        currentFrame = std::min(currentFrame, AnimSequence.FrameCount - 1);
    }
    else if (AnimationType == EAnimationType::LOOP_FOREVER) {
        currentFrame = static_cast<int>(std::fmod(ElapsedTime, AnimSequence.Duration) / timePerFrame);
    }

    olc::vi2d sourcePos = AnimSequence.FirstFrameOffset + olc::vi2d(currentFrame * (AnimSequence.TileSize.x + 1), 0);

    GameWorld::Instance->DrawPartialSprite(InScreenPosition, SpriteSheet, sourcePos, AnimSequence.TileSize);
}
