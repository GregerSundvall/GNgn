#pragma once
#include <iostream>
#include "../Engine/DrawSystem.h"
#include "../Engine/EntitySystem.h"


class Game
{
    bool isRunning = true;
    int PlayerEntityID = -1;
    int EnemiesToSpawn = 100;
    // std::vector<int> EnemyEntityIDs; 
    
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
    void SpawnBullet();    
    void SpawnEnemy(float xPos);
    void SpawnPlayer();
    void NotifyIdChanged(int oldEntityID, int newEntityID) { if (oldEntityID == PlayerEntityID){ PlayerEntityID = newEntityID;}; }
    void NotifyEntityDestroyed(int eID) { if (eID == PlayerEntityID) { PlayerEntityID = -1; std::cout << "GAME OVER" << std::endl; } }
    void Destroy();
};
