#pragma once


#include "Collision.h"
#include "Enemies.h"
#include "Player.h"



class Game
{
    bool isRunning = true;
    Player* player;
    Collision collision;
    Enemies enemies;

public:
    Game()
    {
        player = new Player;
        collision = Collision();
        enemies = Enemies();

    }

    bool Overlap(float aX, float aY, float bX, float bY);
    void Update();
    void Destroy();
};
