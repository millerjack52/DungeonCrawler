#pragma once
#include "olcPixelGameEngine.h"
#include "Player.h"
#include "TArray.h"
#include "Enemy.h"
#include "NotificationManager.h"
#include "Notification.h"
#include <cstdlib>
#include <ctime>
#include "AnimatedSprite.h"
#include "Room.h"
#include "Boss.h"

class Enemy;
class Player;

class GameWorld : public olc::PixelGameEngine
{
public:
    static GameWorld* Instance;

    GameWorld();
    ~GameWorld();

    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;
    olc::Sprite* Tileset;
    TArray<Enemy*>& GetEnemies();
    void GenerateEnemiesForRoom();
    void HandleDoorInteraction();

    NotificationManager notificationManager;
    bool gameCompleted = false;
    bool gameOver = false;

    bool keyPlaced = false;
    bool keyCollected = false;
    olc::vi2d keyPosition;

protected:
    Player* player = nullptr;
    int EnemyCount = 8;
    TArray<Enemy*> Enemies;
    float completionTimer = 0.0f;
    Room* currentRoom = nullptr;
    Room* finalRoom = nullptr;
};
