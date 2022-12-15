#include "Game.h"
#include <random>
#include "Engine.h"


Game::Game()
{
    drawSystem = new DrawSystem;
    entitySystem = new EntitySystem(drawSystem);
    SpawnPlayer();
}

void Game::Start()
{
    
}

void Game::Update()
{
    if (!isRunning) { return; }
    
    // if (EnemiesToSpawn > 0)
    // {
    //     SpawnEnemy();
    // }
    
    entitySystem->Update();
    drawSystem->DrawAll();
}

void Game::SpawnEnemy()
{
    // std::uniform_int_distribution<int> distribution(0, 8000);
    // auto randomX = static_cast<float>(distribution(generator)) / 10;
    // EnemyEntityIDs.push_back(entitySystem->CreateEntity(Float2(randomX, 0)));
}

void Game::SpawnPlayer()
{
    PlayerEntityID = entitySystem->CreateEntity();
    entitySystem->AddTransform(PlayerEntityID, Float2(400, 900), Float2(32, 32));
    entitySystem->AddCollider(PlayerEntityID);
    entitySystem->AddSprite(PlayerEntityID, Color(100, 100, 100));
}

void Game::Destroy()
{
    entitySystem->Destructor();
}
