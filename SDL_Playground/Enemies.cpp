#include "Enemies.h"
#include <SDL_render.h>
#include <utility>
#include "Engine.h"

void Enemies::Update()
{
    if (enemiesToSpawn > 0)
    {
        ActivateEnemy();
    }

    for (int i = 0; i < 30000; i+=3)
    {
        if (enemies[i] >= 0)
        {
            enemies[i+1] += 0.1f;
            enemies[i] += rand() %200 * 0.001 -0.1;
            SDL_SetRenderDrawColor(renderer, (int)enemies[i+2], 100, 100, 255);
            SDL_Rect enemyRect = {static_cast<int>(enemies[i]), static_cast<int>(enemies[i + 1]), 4, 4};
            SDL_RenderFillRect(renderer, &enemyRect);
        }

    }
}

void Enemies::ActivateEnemy()
{
    int count = std::min(5, enemiesToSpawn);
    
    for (int i = 3; i < count; i+=3)
    {
        enemies[lastIndexSpawned + i] = 0;
        enemies[lastIndexSpawned + i + 1] = rand() % 800;
        enemies[lastIndexSpawned + i + 2] = rand() % 100 + 50;
        lastIndexSpawned += i;
        enemiesToSpawn --;
    }
}
