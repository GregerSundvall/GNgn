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
        float x = static_cast<float>(distribution(generator) / 10);
        SpawnEnemy(x, 0, 100);
        enemiesToSpawn--;
    }

    for (int i = 0; i < enemyCount; ++i)
    {
        transforms[i].y += transforms[i].speed * dTime;
    }

    for (int i = 0; i < enemyCount; ++i)
    {
        if (transforms[i].y > 1000)
        {
            DestroyEnemy(i);
            continue;
        }
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        SDL_Rect enemyRect = {  static_cast<int>(transforms[i].x),
                                static_cast<int>(transforms[i].y), 4, 4};
        SDL_RenderFillRect(renderer, &enemyRect);
    }
    
}
void Enemies::SpawnEnemy(float x, float y, float speed)
{
    Enemy enemy = Enemy(x, y, speed);
    
    if (recycledIndexes.size() > 0) // Recycled index available, use that.
    {
        transforms[recycledIndexes.back()] = enemy;
        recycledIndexes.pop_back();
    }
    else  // No recycled indexes available, use a fresh index.
    {
        transforms.push_back(enemy);
        // nextFreshIndex++;
    }


    enemyCount++;
}

void Enemies::DestroyEnemy(int id)
{
    transforms[id] = Enemy();
    recycledIndexes.push_back(id);
    enemyCount--;
}


