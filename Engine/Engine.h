#pragma once
#include "Input.h"
#include "Entity/EntitySystem.h"
#include "Graphics/Graphics.h"

class Entity;


class Engine{
	int width, height;
	
	Graphics* graphics;
	EntitySystem* entities;
	Input* input;
	
public:
	Engine(int width, int height);
	~Engine();

	void Run();
	static Entity* AddGameObject();
	static void ShutDown();

};
