#pragma once
#include <SDL.h>
#include <string>
#include <vector>

#include "../Misc/Vector2.h"




static SDL_Window* window;
static SDL_Renderer* renderer;
static std::vector<SDL_Texture*> textures;
static std::vector<std::string> paths;
static int offsetX;
static int offsetY;

class Graphics
{
public:
	static bool Init();
	static void Update();
	static void WriteToBuffer();
	static void Stop();
	
	static int AddTexture(const char* filePath);
	static SDL_Rect CreateRect(Vector2 position, Vector2 size);
};

