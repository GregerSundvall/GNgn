#pragma once
#include "EntitySystem.h"


class Game
{
    bool isRunning = true;
    int PlayerEntityID;
    int EnemiesToSpawn = 100;
    std::vector<int> EnemyEntityIDs;

    
    EntitySystem* entitySystem = new EntitySystem;
    // Event system
    // Move input system here?
    // Move SDL stuff here?
    // Move all in this class to main?

public:

    void Start();
    void SpawnEnemy();
    void Update();
    void Destroy();
};
