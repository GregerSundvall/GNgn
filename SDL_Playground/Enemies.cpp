#include "Enemies.h"

#include <ctime>
#include <SDL_render.h>
#include <random>
#include "Engine.h"

void Enemies::Update()
{
    if (enemySpawnQueue > 0)
    {
        std::uniform_int_distribution<int> distribution(0, 8000);
        float x = static_cast<float>(distribution(generator) / 10);
        SpawnEnemy(x, 0, 100);
        enemySpawnQueue--;
    }

    // Take any "empties" in array into account when looping
    int maxIndex = enemyCount + recycledIndexes.size();
    
    // Update positions
    for (int i = 0; i < maxIndex; ++i)
    {
        if (transforms[i].id >= 0) // If enemy is active
        {
            transforms[i].y += transforms[i].speed * dTime;   
        }
    }

    // Destroy or draw enemy
    for (int i = 0; i < maxIndex; ++i)
    {
        if (transforms[i].y > 1000)
        {
            DestroyEnemy(i);
            continue;
        }
        
        if (transforms[i].id >= 0) // If enemy is active
        {
            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
            SDL_Rect enemyRect = {  static_cast<int>(transforms[i].x),
                                    static_cast<int>(transforms[i].y),
                                    4, 4};
            SDL_RenderFillRect(renderer, &enemyRect);
        }
    }
    
}
void Enemies::SpawnEnemy(float x, float y, float speed)
{
    Enemy enemy = Enemy(x, y, speed);
    int index;
    
    if (recycledIndexes.size() > 0) // Recycled index available, use that.
    {
        index = recycledIndexes.back();
        transforms[index] = enemy;
        recycledIndexes.pop_back();
    }
    else  // No recycled indexes available, use a fresh index.
    {
        transforms.push_back(enemy);
        index = nextFreshIndex;
        nextFreshIndex++;
    }
    transforms[index].id = index; // Let enemy know it's own index
    enemyCount++;
}

void Enemies::DestroyEnemy(int id)
{
    transforms[id] = Enemy(); // Clear this enemy's data
    recycledIndexes.push_back(id); // Make index available for reuse
    enemyCount--;
}

void Enemies::Destroy()
{
    transforms.clear();
    recycledIndexes.clear();
}


