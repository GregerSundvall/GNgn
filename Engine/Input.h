#pragma once
#include <SDL_stdinc.h>
#include <string>
#include <vector>


static const Uint8* keyStates;

class Input
{
public:
	static void Init();
	static void Update();
	static bool IsDown(int key);
};
