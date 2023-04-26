#pragma once
#include <SDL_stdinc.h>


static const Uint8* keyStates;

class Input
{
public:
	static void Init();
	static void Update();
	static bool KeyIsDown(int key);
	static bool KeyWasPressed(int key);
	static bool KeyWasReleased(int key);
};
