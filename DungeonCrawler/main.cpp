#define OLC_PGE_APPLICATION

#include "GameWorld.h"
#include <iostream>

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 240
#define PIXEL_SIZE 4



int main()
{
    std::cout << "STARTING PROGRAM" << std::endl;

    GameWorld World;

    if (World.Construct(SCREEN_WIDTH, SCREEN_HEIGHT, PIXEL_SIZE, PIXEL_SIZE))
    {
        World.Start();
    }


    return 0;
}
