#include "Engine.h"


Engine::Engine(int width, int height)
{
	graphics = new Graphics(width, height);

}

Engine::~Engine()
{
	delete graphics;
	// delete input;
}

void Engine::ShutDown() {}
