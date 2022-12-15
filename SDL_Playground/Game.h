#pragma once
#include "DrawSystem.h"
#include "Engine.h"
#include "EntitySystem.h"


class Game
{
    bool isRunning = true;
    int PlayerEntityID = -1;
    int EnemiesToSpawn = 100;
    std::vector<int> EnemyEntityIDs;
    
    DrawSystem* drawSystem;
    EntitySystem* entitySystem;
    // Event system?
    // Move input system here?
    // Move SDL stuff here?
    // Move all in this class to main?

public:
    Game();
    void Start();
    void Update();
    void SpawnEnemy();
    void SpawnPlayer();
    void Destroy();
};
