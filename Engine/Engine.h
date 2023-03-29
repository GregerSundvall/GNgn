#pragma once
#include "Input.h"
#include "Graphics/Graphics.h"

class Engine
{
	{ {double x;double y;}Graphics* graphics;
	// static Input* input;
	
public:
	Engine();
	~Engine();
	static void ShutDown();

	// Graphics* Graphics();
};
