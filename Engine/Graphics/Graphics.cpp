#include "Graphics.h"
#include <iostream>
#include <SDL_image.h>
// #include <SDL2_gfxPrimitives.h>


bool Graphics::Start() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "SDL Init error" << std::endl;
		return false;
	}
	window = SDL_CreateWindow("GNgn", 100, 100, 1920, 1080, SDL_WINDOW_SHOWN);
	if (!window) {
		std::cerr << "SDL window error" << std::endl;
		return false;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		std::cerr << "SDL renderer error" << std::endl;
		return false;
	}
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		return false;
	}

	return true;
}

// int Graphics::AddTexture(const char* filePath) {
// 	auto texture = IMG_LoadTexture(renderer, filePath);
// 	textures.push_back(texture);
// 	return textures.size() -1;
// }

void Graphics::Update()
{
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor( renderer, 10, 15, 20, 255 ); // Background color
	Draw();		
	SDL_RenderPresent(renderer);
	SDL_Delay(16); 
}

void Graphics::Draw() {
	SDL_Texture* texture = IMG_LoadTexture(renderer, "Game/Assets/player.png");
	SDL_Rect destination = {100,100,32,32};
	SDL_RenderCopy(renderer, texture, nullptr, &destination);
}

void Graphics::Stop() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}
