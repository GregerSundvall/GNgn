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
    
    // {   // Temporary player input
    //     if (PlayerEntityID >= 0)
    //     {
    //         Float2 velocity = Float2(input->A * -1.0f + input->D * 1.0f, 0);
    //         entitySystem->SetVelocity(PlayerEntityID, velocity);
    //
    //         if (input->Space == 1)
    //         {
    //             SpawnBullet();
    //         }
    //     }
    // }
}



void Game::SpawnBullet()
{
    float x = entitySystem->GetPosition(PlayerEntityID)->x;
    float y = entitySystem->GetPosition(PlayerEntityID)->y -17;
    
    int eID = entitySystem->CreateEntity();
    entitySystem->AddTransform(eID, Float2(x, y), Float2(8, 8));
    entitySystem->AddCollider(eID);
    entitySystem->AddMovement(eID, Float2(0, -3.f));
    entitySystem->AddSprite(eID, Color(200, 200, 0));
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
    entitySystem->AddMovement(PlayerEntityID, Float2(0, 0));
}

void Game::Destroy()
{
    entitySystem->Destructor();
}
