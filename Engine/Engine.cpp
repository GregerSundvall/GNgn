#include "Engine.h"
#include "Input.h"
#include "Entity/Entities.h"
#include "Graphics/Graphics.h"

double Engine::deltaTime;
double Engine::previousFrameTime;
int Engine::pixelsPerMeter;

void Engine::Init(const int windowWidth, const int windowHeight) {
	Graphics::Init(windowWidth, windowHeight);
	Input::Init();
	Entities::Init();
	physics = new Physics(9.8);
}

void Engine::Run() {
	isRunning = true;
	while (isRunning)
	{
		Input::Update();
		Entities::Update();
		physics->Update(deltaTime);
		Entities::UpdateSprites();
		Graphics::Update();
	}

	// Destroy stuff
	
	Graphics::Stop();
}

void Engine::Stop() { isRunning = false; }
int Engine::PixelsPerMeter() { return pixelsPerMeter; }
void Engine::PixelsPerMeter(const int newValue) { pixelsPerMeter = newValue;}
double Engine::DeltaTime() { return deltaTime; }
void Engine::CalculateDeltaTime() {
	const double currentTime = SDL_GetTicks() * 0.001; 
	deltaTime = currentTime - previousFrameTime;
	previousFrameTime = currentTime;
}
