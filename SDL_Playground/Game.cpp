#include "Game.h"
#include <random>
#include "Engine.h"


void Game::Start()
{
    // PlayerEntityID = entitySystem->CreateEntity();
}

void Game::SpawnEnemy()
{
    // std::uniform_int_distribution<int> distribution(0, 8000);
    // auto randomX = static_cast<float>(distribution(generator)) / 10;
    // EnemyEntityIDs.push_back(entitySystem->CreateEntity(Float2(randomX, 0)));
}

void Game::Update()
{
    // if (!isRunning) { return; }
    //
    // if (EnemiesToSpawn > 0)
    // {
    //     SpawnEnemy();
    // }
    //
    // entitySystem->Update();
    drawSystem->DrawAll();
}

void Game::Destroy()
{
    entitySystem->Destructor();
}
