#include "Engine.h"
#include "Input.h"
#include "Entity/Entities.h"
#include "Graphics/Graphics.h"


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
		physics->Update(0.16);
		Graphics::Update();
	}

	// Destroy game?
	// Destroy entities
	// Destroy input?
	// Destroy physics
	Graphics::Stop();
}

void Engine::Stop() { isRunning = false; }
int Engine::GetPixelsPerMeter() { return pixelsPerMeter; }
void Engine::SetPixelsPerMeter(int const value) { pixelsPerMeter = value;}
Entity* Engine::CreatePhysicsEntity(const double x, const double y, const double width, const double height, const double mass, const char* imagePath) {
	return Entities::Create(x, y, width, height, mass, imagePath);
}
