#pragma once
#include <iostream>

#include "DrawSystem.h"
#include "Engine.h"
#include "EntitySystem.h"


class Game
{
    bool isRunning = true;
    int PlayerEntityID = -1; // Will need updates on ID changes.
    int EnemiesToSpawn = 100;
    // std::vector<int> EnemyEntityIDs; // Needs updates on entity ID changes.
    
    DrawSystem* drawSystem;
    EntitySystem* entitySystem;
    // Event system!
    // Move input system here?
    // Move SDL stuff here?
    // Move all in this class to main?

public:
    Game();
    void Start();
    void Update();
    // void HandleCollisions();
    void SpawnBullet();    
    void SpawnEnemy(float xPos);
    void SpawnPlayer();
    void NotifyIdChanged(int oldEntityID, int newEntityID) { if (oldEntityID == PlayerEntityID){ PlayerEntityID = newEntityID;}; }
    void NotifyEntityDestroyed(int eID) { if (eID == PlayerEntityID) { PlayerEntityID = -1; std::cout << "game over" << std::endl; } }
    void Destroy();
};
