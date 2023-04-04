#pragma once
#include "Physics/Physics.h"
// #include "Input.h"
// #include "Entity/EntitySystem.h"
// #include "Graphics/Graphics.h"


class Entity;

static bool isRunning = false;
static int pixelsPerMeter = 15;
static Physics* physics;

class Engine
{
	int width, height;
	// bool GFXStarted;
	
	// Graphics* graphics;
	// EntitySystem* entities;
	// Input* input;
	
public:
	Engine() = default;
	~Engine() = default;

	static void Init();
	static void Run();
	static void Stop();
	static int GetPixelsPerMeter();
	static void SetPixelsPerMeter(int const value);
};
