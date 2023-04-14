#pragma once
#include <SDL.h>
#include <string>
#include <vector>

#include "../Misc/Vector2.h"


class Sprite;




class Graphics
{
	static SDL_Window* window;
	static SDL_Renderer* renderer;

	static std::vector<SDL_Texture*> textures;
	static std::vector<std::string> paths;
	static std::vector<Sprite> sprites;

	static int offsetX;
	static int offsetY;
	static int width;
	static int height;
public:
	static bool Init(int windowWidth, int windowHeight);
	static void Update();
	static void WriteToBuffer();
	static void Stop();
	static std::vector<Sprite>* Sprites();
	
	static SDL_Texture* AddTexture(const char* filePath);
	static SDL_Rect CreateRect(Vector2 position, Vector2 size);
};

