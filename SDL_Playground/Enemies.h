#pragma once
#include <vector>
#include <random>

struct Enemy
{
    float x;
    float y;
    float speed;

    int id;

    Enemy()
    {
        x = -1;
        y = -1;
        speed = 0;
        id = -1;
    }

    Enemy(float x, float y, float speed)
    {
        this->x = x;
        this->y = y;
        this->speed = speed;
        this->id = -1;
    }
};

class Enemies
{
public:
    std::vector<Enemy> transforms;
    std::vector<int> recycledIndexes;
    int enemyCount = 0;
    int nextFreshIndex = 0;
    int enemySpawnQueue = 1000;
    
    std::default_random_engine generator;
    
    Enemies()
    {
        generator.seed(static_cast<unsigned>(time(nullptr)));
    }

    void Update();
    void SpawnEnemy(float x, float y, float speed);
    void DestroyEnemy(int id);
    void Destroy();
    

};
