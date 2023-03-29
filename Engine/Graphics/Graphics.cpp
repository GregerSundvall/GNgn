#include "Graphics.h"
#include <iostream>
#include <SDL_image.h>
#include <SDL2_gfxPrimitives.h>

Graphics::Graphics()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
	{
		std::cerr << "SDL Init error" << std::endl;
	}
	window = SDL_CreateWindow("GNgn", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
	if (!window) 
	{
		std::cerr << "SDL window error" << std::endl;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		std::cerr << "SDL renderer error" << std::endl;
	}
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
	{
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
	}
	
	running = true;
	std::string path = "Game/Assets/player.png";
	texture = IMG_LoadTexture(renderer, "Game/Assets/player.png");
	SDL_Rect destination = {100,100,32,32};

	while (running)
	{
		SDL_Event event;
		while(SDL_PollEvent(&event)) 
		{
			switch(event.type)
			{
			case SDL_QUIT:
				{
					running = false;
					break;
				}
			case SDL_KEYDOWN:
				{
					int scancode = event.key.keysym.scancode;
					if (scancode == SDL_SCANCODE_ESCAPE)
						running = false;
					break;
				}
			default: {};
			}
		}
		SDL_RenderClear(renderer);
		
		// Render stuff
		SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderCopy(renderer, texture, nullptr, &destination);
		
		SDL_RenderPresent(renderer);
		SDL_Delay(16); 
	}
	
}


Graphics::~Graphics()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Graphics::Draw() {}
