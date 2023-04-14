#include "Graphics.h"
#include <iostream>
#include <SDL_image.h>

#include "../Engine.h"
#include "../Entity/Entities.h"
// #include <SDL2_gfxPrimitives.h>

#include "../Physics/RigidBody.h"

int Graphics::width;
int Graphics::height;
std::vector<Sprite> Graphics::sprites;


bool Graphics::Init(const int windowWidth, const int windowHeight) {
	width = windowWidth;
	height = windowHeight;
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
	for (int i = 0; i < sprites.size(); ++i) {
		SDL_RenderCopy(renderer, sprites.at(i).texture, nullptr, &sprites.at(i).rect);
	}
	sprites.clear();

	// // TODO temp stuff
	// std::vector<Sprite>* sprites = Entities::GetSprites();
	// std::cout << sprites->size() << "\n";
	
	// for (auto rb : rigidBodies) {
	// 	if (rb->shape->GetType() == BOX) {
	// 		Box* box = (Box*)rb->shape;
	// 		if (rb->texture) {
	// 			SDL_Rect destination = {(int)rb->position.x, (int)rb->position.y, (int)box->width, (int)box->height};
	// 			SDL_RenderCopyEx(renderer, rb->texture, NULL, &destination,
	// 				0, NULL, SDL_FLIP_NONE);
	// 		}	
	// 	}
	// }
}

void Graphics::Stop() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

std::vector<Sprite>* Graphics::GetSprites() {
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

SDL_Rect Graphics::CreateRect(Vector2 position, Vector2 size) {
	SDL_Rect rect = {
		(int)(position.x + offsetX - size.x * 0.5),
		(int)(-position.y + offsetY - size.y * 0.5),
		(int)size.x, (int)size.y};
	return rect;
}
