﻿#include"Game.h"
#include "../Engine/Entity/Entities.h"
#include "../Engine/Engine.h"


Game::Game()
{
	Engine::PixelsPerMeter(50);
	auto box = Entities::Create(100, 100, 32, 32, 1, "./Game/Assets/player.png");
	auto box2 = Entities::Create(200, 100, 32, 32, 10, "./Game/Assets/player.png");


	// Entity* player0 = EntitySystem::CreateEntity(-500, 500, 32, 32, "./Game/Assets/player.png");
	// Entity* player1 = EntitySystem::CreateEntity(-400, 400, 32, 32, "./Game/Assets/player.png");
	// Entity* player2 = EntitySystem::CreateEntity(-300, 300, 32, 32, "./Game/Assets/player.png");
	// Entity* player3 = EntitySystem::CreateEntity(-200, 200, 32, 32, "./Game/Assets/player.png");
	// Entity* player4 = EntitySystem::CreateEntity(-100, 100, 32, 32, "./Game/Assets/player.png");
	// Entity* player5 = EntitySystem::CreateEntity(0, 0, 32, 32, "./Game/Assets/player.png");
	// Entity* player6 = EntitySystem::CreateEntity(100, -100, 32, 32, "./Game/Assets/player.png");
	// Entity* player7 = EntitySystem::CreateEntity(200, -200, 32, 32, "./Game/Assets/player.png");
	// Entity* player8 = EntitySystem::CreateEntity(300, -300, 32, 32, "./Game/Assets/player.png");
	// Entity* player9 = EntitySystem::CreateEntity(400, -400, 32, 32, "./Game/Assets/player.png");
	
}

Game::~Game()
{
}

