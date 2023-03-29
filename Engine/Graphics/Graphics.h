#pragma once
#include <SDL.h>

class Sprite
{
	SDL_Rect rect;
	SDL_Texture* texture;
};

class Graphics
{
	SDL_Window* window;
	bool running = false;

	SDL_Texture* texture;

public:
	static SDL_Renderer* renderer;
	
	Graphics();
	~Graphics();
	void Draw();
	
};
