#include "GameWorld.h"

GameWorld* GameWorld::Instance = nullptr;

GameWorld::GameWorld()
{
    sAppName = "Dungeon Crawler";
    Instance = this;
}

GameWorld::~GameWorld()
{
    delete player;
    delete Tileset;
    delete currentRoom;
    delete finalRoom;
    for (int i = 0; i < Enemies.Num(); ++i) {
        delete Enemies.GetElement(i);
    }
    Instance = nullptr;
}

bool GameWorld::OnUserCreate()
{
    srand(static_cast<unsigned int>(time(0)));
    Tileset = new olc::Sprite("tileset.png");

    FAnimSequence playerAnimSeq;
    playerAnimSeq.FirstFrameOffset = olc::vi2d(534, 1);
    playerAnimSeq.TileSize = olc::vi2d(12, 12);

    player = new Player();
    AnimatedSprite* playerSprite = new AnimatedSprite(Tileset, playerAnimSeq, EAnimationType::STILL);
    player->SetAnimatedSprite(playerSprite);

    Room* room1 = new Room("stone");
    Room* room2 = new Room("wood");
    Room* room3 = new Room("brick");

    room1->AddDoor(new Door(olc::vi2d(10, 10), false, room2));
    room2->AddDoor(new Door(olc::vi2d(5, 10), false, room3));
    room3->AddDoor(new Door(olc::vi2d(7, 7), true, nullptr));

    currentRoom = room1;
    finalRoom = room3;
    GenerateEnemiesForRoom();
    return true;
}

TArray<Enemy*>& GameWorld::GetEnemies()
{
    return Enemies;
}

void GameWorld::GenerateEnemiesForRoom()
{
    FAnimSequence bossAnimSeq;
    bossAnimSeq.FirstFrameOffset = olc::vi2d(495, 27);
    bossAnimSeq.TileSize = olc::vi2d(12, 12);

    if (currentRoom == finalRoom)
    {
        Boss* boss = new Boss();
        AnimatedSprite* bossSprite = new AnimatedSprite(Tileset, bossAnimSeq, EAnimationType::STILL);
        boss->SetAnimatedSprite(bossSprite);
        Enemies.AddElement(boss);
    }
    else
    {
        int numEnemies = rand() % 5 + 1;

        FAnimSequence enemyAnimSeq;
        enemyAnimSeq.FirstFrameOffset = olc::vi2d(326, 195);
        enemyAnimSeq.TileSize = olc::vi2d(12, 12);
        enemyAnimSeq.FrameCount = 4;
        enemyAnimSeq.Duration = 1.0f;

        for (int i = 0; i < numEnemies; ++i)
        {
            Enemy* enemy = new Enemy();
            AnimatedSprite* enemySprite = new AnimatedSprite(Tileset, enemyAnimSeq, EAnimationType::LOOP_FOREVER);
            enemy->SetAnimatedSprite(enemySprite);
            Enemies.AddElement(enemy);
        }
    }
}

void GameWorld::HandleDoorInteraction()
{
    if (currentRoom->IsPlayerAtFinalDoor(player->GetGridPosition()))
    {
        if (Enemies.Num() == 0)
        {
            notificationManager.AddNotification("CONGRATULATIONS", olc::vi2d(50, 50), 2.0f);
            notificationManager.AddNotification("WINNER", olc::vi2d(50, 60), 2.0f);
            gameCompleted = true;
            completionTimer = 0.0f;
        }
        else
        {
            notificationManager.AddNotification("DEFEAT ALL ENEMIES", olc::vi2d(50, 70), 2.0f);
        }
    }
    else if (currentRoom->IsPlayerAtAnyDoor(player->GetGridPosition()))
    {
        if (Enemies.Num() == 0)
        {
            Door* door = currentRoom->GetDoorAt(player->GetGridPosition());
            if (door->GetLinkedRoom())
            {
                currentRoom = door->GetLinkedRoom();
                keyPlaced = false;
                keyCollected = false;
                GenerateEnemiesForRoom();
            }
        }
        else
        {
            notificationManager.AddNotification("DEFEAT ALL ENEMIES", olc::vi2d(50, 70), 2.0f);
        }
    }
}


bool GameWorld::OnUserUpdate(float fElapsedTime)
{
    Clear(olc::BLACK);

    if (gameOver)
    {
        notificationManager.UpdateAndDraw(this, Tileset, fElapsedTime);
        return true;
    }

    currentRoom->DrawRoom(this, Tileset);

    if (gameCompleted)
    {
        completionTimer += fElapsedTime;
        if (completionTimer >= 2.0f)
        {
            return true;
        }
        notificationManager.UpdateAndDraw(this, Tileset, fElapsedTime);
        return true;
    }

    int PlayerHealth = player->GetHealth();
    std::string healthStr = std::to_string(PlayerHealth);
    notificationManager.AddNotification("HEALTH", olc::vi2d(0, 200), 2.0f);
    notificationManager.AddNotification(healthStr, olc::vi2d(80, 200), 2.0f);

    for (int i = 0; i < Enemies.Num(); ++i)
    {
        Enemy* enemy = Enemies.GetElement(i);
        enemy->Tick(fElapsedTime, this);

        if (!enemy->IsAlive())
        {
            notificationManager.AddNotification("ENEMY DEFEATED", olc::vi2d(50, 70), 2.0f);
            delete enemy;
            Enemies.RemoveElement(i);
            i--;
        }
    }
    if (Enemies.Num() == 0 && !keyPlaced)
    {
        keyPosition = olc::vi2d(rand() % GRID_WIDTH, rand() % GRID_HEIGHT);
        notificationManager.AddNotification("PICK UP THE KEY", olc::vi2d(50, 70), 2.0f);
        currentRoom->PlaceKey(keyPosition);
        keyPlaced = true;
    }
    if (keyPlaced && !keyCollected)
    {
        if (currentRoom->IsKeyPickedUp(player->GetGridPosition()))
        {
            notificationManager.AddNotification("KEY PICKED UP", olc::vi2d(50, 70), 2.0f);
            keyCollected = true;
        }
    }

    if (!keyCollected && currentRoom->IsPlayerAtAnyDoor(player->GetGridPosition()))
    {
        notificationManager.AddNotification("GET THE KEY", olc::vi2d(50, 70), 2.0f);
    }
    else
    {
        HandleDoorInteraction();
    }

    notificationManager.UpdateAndDraw(this, Tileset, fElapsedTime);
    player->Tick(fElapsedTime, this);

    return true;
}
