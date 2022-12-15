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
    
    EntitySystem* entitySystem = new EntitySystem;
    DrawSystem* drawSystem = new DrawSystem;
    // Event system?
    // Move input system here?
    // Move SDL stuff here?
    // Move all in this class to main?

public:

    void Start();
    void SpawnEnemy();
    void Update();
    void Destroy();
};
