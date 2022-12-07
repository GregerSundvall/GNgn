#include "Engine.h"

#include <random>

#include "Game.h"
#include "iostream"

SDL_Renderer* renderer;
Input* input;
float dTime = 0.0f;

void Engine::Run()
{
    Uint64 previousTicks = SDL_GetPerformanceCounter();
    float FPScounts[100] = {0};
    int nextFPSIndex = 0;
    float accumulatedFPS = 0;

    input = new Input();
    game = new Game();

    
    while (SDLisRunning)
    {
        Uint64 ticks = SDL_GetPerformanceCounter();
        Uint64 deltaTicks = ticks - previousTicks;
        previousTicks = ticks; 
        dTime = (float)deltaTicks / SDL_GetPerformanceFrequency();
        float currentFPS = 1 / dTime;
        FPScounts[(nextFPSIndex)] = currentFPS;
        accumulatedFPS += currentFPS;
        if (nextFPSIndex == 99)
        {
            nextFPSIndex = 0;
            std::cout << static_cast<int>(accumulatedFPS / 100) << std::endl;
            accumulatedFPS = 0;
        }
        else
        {
            nextFPSIndex++;
        }
        
        input->Update();
        if (input->Esc) { SDLisRunning = false; break; }
        
        game->Update();
        
        
        SDL_RenderPresent(renderer);
        SDL_Delay(6);
    }

    // Destroy game?
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
