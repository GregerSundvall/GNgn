#pragma once
#include "Physics/Physics.h"
#include "Misc/Misc.h"
// #include "Input.h"
// #include "Entity/EntitySystem.h"
// #include "Graphics/Graphics.h"


class Entity;

static bool isRunning = false;
static Physics* physics;

class Engine
{
	static double deltaTime;
	static double previousFrameTime;
	static int pixelsPerMeter;
public:
	Engine() = default;
	~Engine() = default;

	static void Init(int windowWidth, int windowHeight);
	static void Run();
	static void Stop();
	static int PixelsPerMeter();
	static void PixelsPerMeter(int const newValue);
	static double DeltaTime();
	static void CalculateDeltaTime();
};
