#pragma once

class Enemies
{
public:
    float enemies[90000] = {-3};
    int enemiesToSpawn = 30000;
    // int freeEnemies[30000] = {-1};
    int lastIndexSpawned = -1;
    
    Enemies()
    {

        
    }

    void Update();

private:
    void ActivateEnemy();
};
