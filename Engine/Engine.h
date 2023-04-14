#pragma once
#include "Physics/Physics.h"
#include "Misc/Misc.h"
// #include "Input.h"
// #include "Entity/EntitySystem.h"
// #include "Graphics/Graphics.h"


class Entity;

static bool isRunning = false;
static int pixelsPerMeter = 15;
static Physics* physics;

class Engine
{
public:
	Engine() = default;
	~Engine() = default;

	static void Init(int windowWidth, int windowHeight);
	static void Run();
	static void Stop();
	static int GetPixelsPerMeter();
	static void SetPixelsPerMeter(int const value);
	
	// Create box with physics:
	static Entity* CreatePhysicsEntity(double x, double y, double width, double height, double mass, const char* imagePath);
};
