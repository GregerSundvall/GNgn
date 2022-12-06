#pragma once
#include <vector>
#include <array>
#include <random>

struct Enemy
{
    float x;
    float y;
    float speed;

    Enemy()
    {
        x = -1;
        y = -1;
        speed = 0;
    }

    Enemy(float x, float y, float speed)
    {
        this->x = x;
        this->y = y;
        this->speed = speed;
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
    
    
    std::default_random_engine generator;
    
    Enemies()
    {
        enemies = new Enemy[capacity];
        generator.seed(time(NULL));
    }

    void Update();
    void SpawnEnemy(float x, float y, float speed);

private:
};
