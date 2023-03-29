#include"Game.h"


Game::Game()
{
	engine = new Engine();
}

Game::~Game()
{
	delete engine;
}

void Game::Run()
{
	
}
// Engine* Game::Engine() {return engine;}
