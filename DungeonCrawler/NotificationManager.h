#pragma once
#include "Notification.h"
#include "TArray.h"
#include "olcPixelGameEngine.h"

class NotificationManager
{
public:
    void AddNotification(const std::string& message, olc::vi2d position, float duration);
    void UpdateAndDraw(olc::PixelGameEngine* engine, olc::Sprite* tileset, float fElapsedTime);

private:
    TArray<Notification> notifications;
};
