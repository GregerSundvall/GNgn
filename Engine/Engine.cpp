#include "Engine.h"
#include "Input.h"
#include "Graphics/Graphics.h"


void Engine::Init() {
	Graphics::Init();
	Input::Start();
	physics = new Physics(9.8);
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

void Engine::Stop() { isRunning = false; }
int Engine::GetPixelsPerMeter() { return pixelsPerMeter; }
void Engine::SetPixelsPerMeter(int const value) { pixelsPerMeter = value;}
