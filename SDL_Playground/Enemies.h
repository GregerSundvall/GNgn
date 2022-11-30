#pragma once

class Enemies
{
    float enemies[30000] = {-3};
    int enemiesToSpawn = 10000;
    int freeEnemies[30000] = {-1};
    int lastIndexSpawned = -1;
    
public:
    Enemies()
    {

        
    }

    void Update();

private:
    void ActivateEnemy();
};
