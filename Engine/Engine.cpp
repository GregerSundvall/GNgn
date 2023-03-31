#include "Engine.h"

#include "Graphics/Graphics.h"


void Engine::Run() {
	GFXStarted = Graphics::Init();
	// input = new Input();
	// entities = new EntitySystem();
	
	isRunning = true;
	while (isRunning)
	{
		Graphics::Update();
	}
}

Entity* Engine::AddGameObject() {
	return nullptr;					// TODO just returning nullptr for now
}
void Engine::Stop() {
	isRunning = false;
	
}
