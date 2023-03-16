#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "../Misc/Components.h"
#include <vector>
#include "../Misc/Vector2.h"

struct GraphicsSystem
{
private:
	static int windowWidth;
	static int windowHeight;
	static SDL_Window* window;
	static SDL_Renderer* renderer;
	static Color backgroundColor; 
	static std::vector<Sprite> sprites;
	static std::vector<SDL_Texture*> textures;

public:
	static int WindowWidth;
	static int WindowHeight;

	GraphicsSystem(int width, int height);
	static int AddTexture(std::string filepath);
	static void DrawTexture(Vector2 position, Vector2 size, int textureID);
	static bool Start(); // Starts SDL etc
	static void Stop(); // Stops SDL
	static void ClearScreen(); // Fills screen with 'color'
	static void SetBGColor(Color& newColor); // Change background color
	//static SDL_Renderer* GetRenderer();
	static void Update(float dt);
};

