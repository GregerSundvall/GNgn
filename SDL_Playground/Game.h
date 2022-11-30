#pragma once

#include <cstdlib>

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

    void Update();
};
