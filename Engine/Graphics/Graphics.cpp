#include "Graphics.h"
#include <iostream>
#include <SDL_image.h>

#include "../Engine.h"
#include "../Entity/Entities.h"
// #include <SDL2_gfxPrimitives.h>


int Graphics::width;
int Graphics::height;
std::vector<Sprite> Graphics::sprites;
SDL_Window* Graphics::window;
SDL_Renderer* Graphics::renderer;
std::vector<SDL_Texture*> Graphics::textures;
std::vector<std::string> Graphics::paths;
int Graphics::offsetX;
int Graphics::offsetY;

bool Graphics::Init(const int windowWidth, const int windowHeight) {
	width = windowWidth;
	height = windowHeight;
	offsetX = width / 2;
	offsetY = height / 2;
	sprites.reserve(100);

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
	for (int i = 0; i < sprites.size(); ++i) {
		SDL_RenderCopy(renderer, sprites.at(i).texture, nullptr, &sprites.at(i).rect);
	}
	sprites.clear();
}

void Graphics::Stop() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

std::vector<Sprite>* Graphics::Sprites() {
	return &sprites;
}

SDL_Texture* Graphics::AddTexture(const char* filePath) {
	for (int i = 0; i < paths.size(); ++i){
		if (paths.at(i) == std::string(filePath)){
			return textures.at(i);
		}
	}
	SDL_Texture* texture = IMG_LoadTexture(renderer, filePath);
	textures.push_back(texture);
	paths.push_back(std::string(filePath));
	return texture;
}

SDL_Rect Graphics::CreateRect(const Vector2 position, const Vector2 size) {
	SDL_Rect rect = {
		(int)(position.x + offsetX - size.x * 0.5),
		(int)(-position.y + offsetY - size.y * 0.5),
		(int)size.x, (int)size.y};
	return rect;
}
