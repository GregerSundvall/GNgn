#pragma once
#include <SDL_stdinc.h>
#include <string>
#include <vector>


static const Uint8* keyStates;

class Input
{
public:
	static void Start();
	static void Update();
	static bool KeyIsDown(int key);
	static bool KeyWasPressed(int key);
	static bool KeyWasReleased(int key);
};
