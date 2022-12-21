#include "Engine.h"
#include <random>
#include "Game.h"
#include "iostream"


SDL_Renderer* renderer;
Input* input;
float dTime = 0.0f;
std::default_random_engine generator;


Engine::Engine()
{
    game = new Game;
    
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(
        "SDL2 Test",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width, height,
        SDL_WINDOW_SHOWN);
        
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);

    Run();
};

void Engine::Run()
{
    Uint64 previousTicks = SDL_GetPerformanceCounter();
    float FPScounts[100] = {0};
    int nextFPSIndex = 0;
    float accumulatedFPS = 0;

    input = new Input();
    game = new Game();
    game->Start();
    
    while (SDLisRunning)
    {
        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // FPS stuff
        Uint64 ticks = SDL_GetPerformanceCounter();
        Uint64 deltaTicks = ticks - previousTicks;
        previousTicks = ticks; 
        dTime = static_cast<float>(deltaTicks) / SDL_GetPerformanceFrequency();
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

        // Run update methods
        input->Update();
        if (input->Esc) { SDLisRunning = false; break; } // Stop engine on Esc
        game->Update();

        // Draw
        
        SDL_RenderPresent(renderer);

        // Gimme a reasonable framerate (not like 2000fps)
        SDL_Delay(6);
    }

    game->Destroy();
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
