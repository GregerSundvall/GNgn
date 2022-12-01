#include "Game.h"
#include "Player.h"
#include <SDL.h>

#include "Engine.h"


bool Game::Overlap(float aX, float aY, float bX, float bY)
{
    return (aX + 16 > bX &&
            bX + 2 > aX &&
            aY + 16 > bY &&
            bY + 2 > aY);
}

void Game::Update()
{
    if (!isRunning) { return; }

    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    if (player->isAlive) { player->Update(); }

    enemies.Update();

    // Check every enemy vs every enemy (Extremely slow)
    // for (int i = 0; i < 30000; i+=3)
    // {
    //     for (int j = 0; j < 30000; j+=3)
    //     {
    //         Overlap(enemies.enemies[i], enemies.enemies[i+1],
    //             enemies.enemies[j], enemies.enemies[j+1]);
    //     }
    //
    // }

    
    // Check player vs every enemy
    for (int i = 0; i < 30000; i+=3)
    {
        if (Overlap(player->posX, player->posY,
            enemies.enemies[i], enemies.enemies[i+1]))
        {
            enemies.enemies[i] = -1;
        }
    }

}
