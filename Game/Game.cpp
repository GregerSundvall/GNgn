#include"Game.h"
#include "../Engine/Engine.h"
#include "../Engine/Entity/EntitySystem.h"


Game::Game()
{
	Entity* player1 = EntitySystem::CreateEntity(0, 0, 32, 32, "./Game/Assets/player.png");
	Entity* player2 = EntitySystem::CreateEntity(100, 100, 32, 32, "./Game/Assets/player.png");
	
}

Game::~Game()
{
}

