#include "Game.h"
#include <random>
#include "../Engine/Engine.h"
#include "Player.h"


Game::Game()
{

}

void Game::Start()
{
    player = new Player("greg", 32);
    
    SpawnEnemy(200);
    SpawnEnemy(300);
    SpawnEnemy(400);
    SpawnEnemy(500);
    SpawnEnemy(600);
}

void Game::Update()
{
    if (!isRunning) { return; }
    
    entitySystem->Update();
    drawSystem->Update();
    
    {   // Temporary player input
        if (player->isAlive)
        {
            Float2 velocity = Float2(input->A * -1.0f + input->D * 1.0f, 0);
            player->SetVelocity(velocity);
    
            if (input->Space == 1)
            {
                SpawnBullet();
            }
        }
    }
}


void Game::SpawnBullet()
{
    Float2* playerPos = player->GetPosition();
    float x = playerPos->x;
    float y = playerPos->y -2;
    float size = 8;
    float playerSize = 32;
    
    int eID = entitySystem->CreateEntity();
    entitySystem->AddTransform(eID, Float2(x - size/2.f + playerSize/2.f, y), Float2(size, size));
    entitySystem->AddCollider(eID);
    entitySystem->AddMovement(eID, Float2(0, -10.0f));
    entitySystem->AddSprite(eID, Color(200, 200, 0));
}


void Game::SpawnEnemy(float xPos)
{
    // std::uniform_int_distribution<int> distribution(0, 8000);
    // auto randomX = static_cast<float>(distribution(generator)) / 10;
    // EnemyEntityIDs.push_back(entitySystem->CreateEntity());
    float size = 24;
    int eID = entitySystem->CreateEntity();
    entitySystem->AddTransform(eID, Float2(xPos - size/2.f, 0), Float2(size, size));
    entitySystem->AddCollider(eID);
    entitySystem->AddMovement(eID, Float2(0, 0.5f));
    entitySystem->AddSprite(eID, "Res/Ships/enemy1.png");
}

void Game::NotifyIdChanged(int oldEntityID, int newEntityID)
{ if (oldEntityID == player->EID()){ player->UpdateEID(newEntityID); } }

void Game::NotifyEntityDestroyed(int eID)
{ if (eID == player->EID()) { player->WasKilled(); std::cout << "GAME OVER" << std::endl; } }

void Game::Destructor()
{
    
}
