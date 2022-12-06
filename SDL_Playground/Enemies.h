#pragma once
#include <vector>
#include <array>

struct Enemy
{
    float x;
    float y;

    Enemy()
    {
        x = -1;
        y = -1;
    }

    Enemy(float x, float y)
    {
        this->x = x;
        this->y = y;
    }
};

class Enemies
{
public:
    Enemy* enemies;
    int enemyCount = 0;
    int capacity = 8;
    int nextFreshIndex = 0;
    std::vector<int> recycledIndexes;
    int enemiesToSpawn = 5;
    
    Enemies()
    {
        enemies = new Enemy[capacity];
    }

    void Update();
    void SpawnEnemy(float x, float y);

private:
};
