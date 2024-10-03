#include "NotificationManager.h"

void NotificationManager::AddNotification(const std::string& message, olc::vi2d position, float duration)
{
    notifications.AddElement(Notification(message, position, duration));
}

void NotificationManager::UpdateAndDraw(olc::PixelGameEngine* engine, olc::Sprite* tileset, float fElapsedTime)
{
    for (int i = 0; i < notifications.Num(); ++i)
    {
        Notification& notification = notifications.GetElement(i);
        notification.Update(fElapsedTime);
        notification.Draw(engine, tileset);

        if (notification.IsExpired())
        {
            notifications.RemoveElement(i);
            i -= 1;
        }
    }
}
