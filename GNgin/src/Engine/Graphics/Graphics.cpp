#include "Graphics.h"
#include <iostream>


int GraphicsSystem::AddTexture(std::string filepath) // Returns texture's index in textures array (textureID)
{
	SDL_Texture* texture = IMG_LoadTexture(renderer, filepath.c_str());
	textures.push_back(texture);
	return textures.size() - 1;
}

bool GraphicsSystem::Start()
{
	backgroundColor = Color();

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
	{
		std::cerr << "SDL Init error" << std::endl;
		return false;
	}

	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

	window = SDL_CreateWindow("GNgin", 0, 0, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	if (!window) 
	{
		std::cerr << "SDL window error" << std::endl;
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		std::cerr << "SDL renderer error" << std::endl;
		return false;
	}
	return true;
}

void GraphicsSystem::Stop()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void GraphicsSystem::ClearScreen()
{
	SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	SDL_RenderClear(renderer);
}

void GraphicsSystem::SetBGColor(Color& newColor)
{
	backgroundColor = newColor;
}

//SDL_Renderer* GraphicsSystem::GetRenderer()
//{
//	return renderer;
//}

void GraphicsSystem::Update(float dt)
{

}