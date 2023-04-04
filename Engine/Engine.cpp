#include "Engine.h"
#include "Input.h"
#include "Graphics/Graphics.h"


void Engine::Init() {
	Graphics::Init();
	Input::Start();
	// entities = new EntitySystem();

}

void Engine::Run() {
	isRunning = true;
	while (isRunning)
	{
		Input::Update();
		Graphics::Update();
	}

	// Destroy game?
	// Destroy input?
	// Destroy entities
	// Destroy physics
	Graphics::Stop();
}

Entity* Engine::AddGameObject() {
	return nullptr;					// TODO just returning nullptr for now
}
void Engine::Stop() { isRunning = false; }
