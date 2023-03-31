#pragma once
// #include "Input.h"
// #include "Entity/EntitySystem.h"
// #include "Graphics/Graphics.h"


class Entity;

static bool isRunning = false;

class Engine
{
	int width, height;
	bool GFXStarted;
	
	// Graphics* graphics;
	// EntitySystem* entities;
	// Input* input;
	
public:
	Engine() = default;
	~Engine() = default;

	void Run();
	static Entity* AddGameObject();
	static void Stop();

};
