#pragma once


#include "Enemies.h"
#include "Player.h"



class Game
{
    bool isRunning = true;
    Player* player;
    Enemies enemies;

public:
    Game()
    {
        player = new Player;
        enemies = Enemies();

    }

    bool Overlap(float aX, float aY, float bX, float bY);

    void Update();
};
