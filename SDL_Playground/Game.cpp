#include "Game.h"


void Game::Update()
{
    if (!isRunning) { return; }

    entitySystem->Update();
}

void Game::Destroy()
{
    entitySystem->Destroy();
}
