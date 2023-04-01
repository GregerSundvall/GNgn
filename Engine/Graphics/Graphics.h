#pragma once
#include <SDL.h>
#include <vector>


static SDL_Window* window;
static SDL_Renderer* renderer;

class Graphics
{
public:
	// static bool running = false;
	// static int width, height;

	// static std::vector<SDL_Texture*> textures;
	//
	// static SDL_Texture* texture;
	
	static bool Start();
	// static int AddTexture(const char* filePath);
	static void Update();
	static void Draw();
	static void Stop();
};
