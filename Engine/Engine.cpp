#include "Engine.h"


Engine::Engine()
{
	graphics = new Graphics();
	// input = new Input();
}


// Graphics* Engine::Graphics() {return graphics;}

Engine::~Engine()
{
	delete graphics;
	// delete input;
}

void Engine::ShutDown() {}
