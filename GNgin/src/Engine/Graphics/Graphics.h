#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "../Misc/Components.h"
struct GraphicsSystem
{
private:
	static int windowWidth;
	static int windowHeight;
	static SDL_Window* window;
	static SDL_Renderer* renderer;
	static Color color;

public:
	static int WindowWidth;
	static int WindowHeight;
	static bool Start();
	static void Stop();
	static void ClearScreen();
	static void SetBGColor(Color& newColor);
	//static SDL_Renderer* GetRenderer();
};

