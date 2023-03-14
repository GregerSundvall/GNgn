#include "Engine.h"
#include <random>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "iostream"
#include "../SpaceShooter/Game.h"


DrawSystem* drawSystem;
InputSystem* input;
Game* game;
EntitySystem* entitySystem;
float dTime = 0.0f;
std::default_random_engine generator;

Engine::Engine()
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    
    window = SDL_CreateWindow("GEngn", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        width, height, SDL_WINDOW_SHOWN);
        
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);
    
    drawSystem = new DrawSystem(renderer);
    input = new InputSystem();
    game = new Game();
    entitySystem = new EntitySystem(this);
    game->Start();

    MainLoop();
        
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
};

void Engine::MainLoop()
{
    while (isRunning)
    {
        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Run update methods
        input->Update();
        if (input->Esc) { isRunning = false; continue; } // Stop engine on Esc
        game->Update();
        entitySystem->Update();
        drawSystem->Update();
    
        // Draw
        SDL_RenderPresent(renderer);

        // Gimme a reasonable framerate (not like 2000fps)
        SDL_Delay(6);
    
        CalculateFPS();
    }
}

void Engine::CalculateFPS()
{
    Uint64 ticks = SDL_GetPerformanceCounter();
    Uint64 deltaTicks = ticks - previousTicks;
    previousTicks = ticks; 
    dTime = static_cast<float>(deltaTicks) / SDL_GetPerformanceFrequency();
    float currentFPS = 1 / dTime;
    FPScounts[nextFPSIndex] = currentFPS;
    accumulatedFPS += currentFPS;
    if (nextFPSIndex == 99)
    {
        nextFPSIndex = 0;
        frameRate = static_cast<int>(accumulatedFPS / 100);
        std::cout << frameRate << std::endl;
        accumulatedFPS = 0;
    }
    else
    {
        nextFPSIndex++;
    }
}

int Engine::FrameRate()
{
    return frameRate;
}


