#include "Graphics.h"
#include <iostream>
#include <SDL_image.h>

#include "../Entity/EntitySystem.h"
// #include <SDL2_gfxPrimitives.h>


bool Graphics::Init() {
	int width = 1920;
	int height = 1080;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "SDL Init error" << std::endl;
		return false;
	}
	window = SDL_CreateWindow("GNgn", 100, 100, width, height, SDL_WINDOW_SHOWN);
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

	offsetX = width / 2;
	offsetY = height / 2;
	return true;
}

void Graphics::Update(){
	SDL_SetRenderDrawColor( renderer, 10, 15, 20, 255 ); // Background color
	SDL_RenderClear(renderer);
	WriteToBuffer();		
	SDL_RenderPresent(renderer);
	SDL_Delay(16); 
}

void Graphics::WriteToBuffer() {
	std::vector<Sprite>* sprites = EntitySystem::SpritesToDraw();
	for (int i = 0; i < sprites->size(); ++i) {
		Sprite sprite = sprites->at(i);
		SDL_Rect destination = CreateRect(sprite.position, sprite.size);
		SDL_RenderCopy(renderer, textures.at(sprite.textureID), nullptr, &destination);
	}
	delete sprites;
}

void Graphics::Stop() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

int Graphics::AddTexture(const char* filePath) {
	for (int i = 0; i < paths.size(); ++i){
		if (paths.at(i) == std::string(filePath)){
			return i;
		}
	}
	SDL_Texture* texture = IMG_LoadTexture(renderer, filePath);
	textures.push_back(texture);
	paths.push_back(std::string(filePath));
	return textures.size() -1;
}

SDL_Rect Graphics::CreateRect(Vector2 position, Vector2 size) {
	SDL_Rect rect = {
		(int)(position.x + offsetX - size.x * 0.5),
		(int)(-position.y + offsetY - size.y * 0.5),
		(int)size.x, (int)size.y};
	return rect;
}
