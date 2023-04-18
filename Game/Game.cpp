#include"Game.h"

#include <iostream>

#include "../Engine/Entity/Entities.h"
#include "../Engine/Engine.h"


Game::Game()
{
	Engine::PixelsPerMeter(500);
	auto box = Entities::Create(100, 100, 32, 32, 100, "./Game/Assets/player.png");
	auto box2 = Entities::Create(200, 100, 32, 32, 1, "./Game/Assets/player.png");
	
}

Game::~Game()
{
}

