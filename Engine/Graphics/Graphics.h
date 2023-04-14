#pragma once
#include <SDL.h>
#include <string>
#include <vector>

#include "../Misc/Vector2.h"


class Sprite;


static SDL_Window* window;
static SDL_Renderer* renderer;
static std::vector<SDL_Texture*> textures;
static std::vector<std::string> paths;
static int offsetX;
static int offsetY;


class Graphics
{
	static int width;
	static int height;
	static std::vector<Sprite> sprites;
public:
	static bool Init(int windowWidth, int windowHeight);
	static void Update();
	static void WriteToBuffer();
	static void Stop();
	static std::vector<Sprite>* GetSprites();
	
	static SDL_Texture* AddTexture(const char* filePath);
	static SDL_Rect CreateRect(Vector2 position, Vector2 size);
};

