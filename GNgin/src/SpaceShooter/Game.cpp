#include "Game.h"
#include <iostream>
#include <random>
#include "../Engine/Engine.h"
#include "Player.h"
#include "UI.h"


void Game::Start()
{
    int t = GraphicsSystem::AddTexture("../../assets/Ships/player.png");
    Entity e = Entity();
    e.AddSprite(t);
    //player = new Player("greg", 32, this);
    //SpawnEnemy(200);
    //SpawnEnemy(300);
    //SpawnEnemy(400);
    //SpawnEnemy(500);
    //SpawnEnemy(600);
    //auto ui = new UI();

    isRunning = true;
}

void Game::Update()
{
    //player->Update();
}


void Game::SpawnBullet(Float2 position, Float2 velocity, float size)
{
    int eID = entitySystem->CreateEntity();
    entitySystem->AddTransform(eID, Float2(position), Float2(size, size));
    entitySystem->AddCollider(eID);
    entitySystem->AddMovement(eID, velocity);
    entitySystem->AddSprite(eID, Color(200, 200, 0));
}


void Game::SpawnEnemy(float xPos)
{
    //// std::uniform_int_distribution<int> distribution(0, 8000);
    //// auto randomX = static_cast<float>(distribution(generator)) / 10;
    //// EnemyEntityIDs.push_back(entitySystem->CreateEntity());
    //float size = 24;
    //int eID = entitySystem->CreateEntity();
    //entitySystem->AddTransform(eID, Float2(xPos - size/2.f, 0), Float2(size, size));
    //entitySystem->AddCollider(eID);
    //entitySystem->AddMovement(eID, Float2(0, 0.5f));
    //entitySystem->AddSprite(eID, "assets/Ships/enemy1.png");
}

void Game::NotifyIdChanged(int oldEntityID, int newEntityID)
{ if (oldEntityID == player->EID()){ player->UpdateEID(newEntityID); } }

void Game::NotifyEntityDestroyed(int eID)
{ if (eID == player->EID()) { player->WasKilled(); std::cout << "GAME OVER" << std::endl; } }


