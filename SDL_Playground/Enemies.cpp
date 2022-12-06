#include "Enemies.h"

#include <ctime>
#include <SDL_render.h>
#include <random>
#include "Engine.h"

void Enemies::Update()
{
    if (enemiesToSpawn > 0)
    {
        std::uniform_int_distribution<int> distribution(0, 8000);
        int x = distribution(generator) / 10;
        SpawnEnemy(x, 100, 100);
        enemiesToSpawn--;
    }

    for (int i = 0; i < enemyCount; ++i)
    {
        enemies[i].y += enemies[i].speed * dTime;
        if (enemies[i].y > 800)
        {
            continue;
        }
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        SDL_Rect enemyRect = {static_cast<int>(enemies[i].x), static_cast<int>(enemies[i].y), 4, 4};
        SDL_RenderFillRect(renderer, &enemyRect);
    }
    
}
void Enemies::SpawnEnemy(float x, float y, float speed)
{
    Enemy enemy = Enemy(x, y, speed);
    
    if (recycledIndexes.size() > 0) // Recycled index available.
    {
        enemies[recycledIndexes.back()] = enemy;
        recycledIndexes.pop_back();
    }
    else if (nextFreshIndex < capacity) // No recycled indexes available, but still room in array.
    {
        enemies[nextFreshIndex] = enemy;
        nextFreshIndex++;
    }
    else // Array full. Create new larger array, copy all from old, add new enemy.
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


