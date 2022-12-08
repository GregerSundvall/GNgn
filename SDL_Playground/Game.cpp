#include "Game.h"
#include "Player.h"
#include <SDL.h>

#include "Engine.h"


bool Game::Overlap(const float aX, const float aY, const float bX, const float bY)
{
    return (aX + 32 > bX &&
            bX + 4 > aX &&
            aY + 32 > bY &&
            bY + 4 > aY);
}

void Game::Update()
{
    if (!isRunning) { return; }

    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    if (player->isAlive) { player->Update(); }

    enemies.Update();

    
    // Check player vs every enemy
    // for (int i = 0; i < 90000; i+=3)
    // {
    //     if (Overlap(player->posX, player->posY,
    //         enemies.enemies[i], enemies.enemies[i+1]))
    //     {
    //         enemies.enemies[i] = -1;
    //     }
    // }

}

void Game::Destroy()
{
    enemies.Destroy();
}
