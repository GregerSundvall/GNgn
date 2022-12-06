#include "Enemies.h"
#include <SDL_render.h>
#include <utility>
#include "Engine.h"

void Enemies::Update()
{
    if (enemiesToSpawn > 0)
    {
        SpawnEnemy(100, 100);
        enemiesToSpawn--;
    }

    for (int i = 0; i < enemyCount; ++i)
    {
        enemies[i].y += 0.01;
        if (enemies[i].y > 800)
        {
            continue;
        }
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        SDL_Rect enemyRect = {static_cast<int>(enemies[i].x), static_cast<int>(enemies[i].y), 4, 4};
        SDL_RenderFillRect(renderer, &enemyRect);
    }
    
}
void Enemies::SpawnEnemy(float x, float y)
{
    Enemy enemy = Enemy(x, y);

    if (recycledIndexes.size() > 0)
    {
        enemies[recycledIndexes.back()] = enemy;
        recycledIndexes.pop_back();
    }
    else if (nextFreshIndex < capacity)
    {
        enemies[nextFreshIndex] = enemy;
        nextFreshIndex++;
    }
    else
    {
        Enemy* grown = new Enemy[capacity * 2];
        for (int i = 0; i < capacity; ++i)
        {
            grown[i] = enemies[i];
            grown[i] = enemies[i];
        }
        Enemy *enemies = grown;
        capacity *= 2;

        enemies[nextFreshIndex] = enemy;
        nextFreshIndex++;
    }

    enemyCount++;
}

// void Enemies::ActivateEnemy()
// {
//     int count = std::min(5, enemiesToSpawn);
//     
//     for (int i = 3; i < count; i+=3)
//     {
//         enemies[lastIndexSpawned + i] = 0;
//         enemies[lastIndexSpawned + i + 1] = rand() % 800;
//         enemies[lastIndexSpawned + i + 2] = rand() % 100 + 50;
//         lastIndexSpawned += i;
//         enemiesToSpawn --;
//     }
// }

