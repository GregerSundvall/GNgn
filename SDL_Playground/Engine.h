#pragma once
#include <SDL.h>
#include "Game.h"
#include "Input.h"

extern SDL_Renderer* renderer;
extern Input* input;
extern float dTime;

class Engine
{
    SDL_Window* window;
    Game* game;
    const int width = 800;
    const int height = 1000;
    bool SDLisRunning = true;

public:
    
    Engine()
    {
        SDL_Init(SDL_INIT_VIDEO);
        window = SDL_CreateWindow(
            "SDL2 Test",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width, height,
            SDL_WINDOW_SHOWN);
        
        renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);

        
    };

    void Run();
    
    
};
