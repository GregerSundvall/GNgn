#pragma once
#include <iostream>
class Player;

class Game
{
    bool isRunning = true;
    Player* player;
    // int PlayerEntityID = -1;
    // int EnemiesToSpawn = 100;
    // std::vector<int> EnemyEntityIDs; 
    
    
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
    void NotifyIdChanged(int oldEntityID, int newEntityID);
    void NotifyEntityDestroyed(int eID);
    void Destructor();
};
