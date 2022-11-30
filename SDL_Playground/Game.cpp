#include "Game.h"
#include "Player.h"
#include <SDL.h>

#include "Engine.h"


void Game::Update()
{
    if (!isRunning) { return; }

    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    if (player->isAlive) { player->Update(); }

    enemies.Update();

}
