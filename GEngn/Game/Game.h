#pragma once
class Player;

class Game
{
    bool isRunning = false;
    Player* player = nullptr;
    // int PlayerEntityID = -1;
    // int EnemiesToSpawn = 100;
    // std::vector<int> EnemyEntityIDs; 
    

public:
    void Start();
    void Update();
    void SpawnBullet(); // Spawns a moving projectile in front of player
    void SpawnEnemy(float xPos);
    void NotifyIdChanged(int oldEntityID, int newEntityID);
    void NotifyEntityDestroyed(int eID);
};
