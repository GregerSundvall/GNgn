#include "Game.h"
#include <random>
#include "Engine.h"


Game::Game()
{
    drawSystem = new DrawSystem;
    entitySystem = new EntitySystem(drawSystem);
    SpawnPlayer();
    SpawnEnemy();
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
    EnemyEntityIDs.push_back(entitySystem->CreateEntity());
    entitySystem->AddTransform(EnemyEntityIDs[0], Float2(400, 0), Float2(24, 24));
    entitySystem->AddCollider(EnemyEntityIDs[0]);
    entitySystem->AddMovement(EnemyEntityIDs[0], Float2(0, 1.f));
    entitySystem->AddSprite(EnemyEntityIDs[0], Color(150, 50, 100));
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
