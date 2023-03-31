#include"Game.h"

#include <SDL_keycode.h>

#include "../Engine/Engine.h"
#include "../Engine/Input.h"


Game::Game()
{
	auto asdf = Engine::AddGameObject();
	
}

Game::~Game()
{
}

void Game::Run()
{
	int inputForward = SDL_SCANCODE_W;

	if (Input::IsDown(inputForward))
	{
		
	}

}
// Engine* Game::Engine() {return engine;}
