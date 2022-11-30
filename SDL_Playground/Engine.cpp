#include "Engine.h"
#include "Game.h"
#include "iostream"

SDL_Renderer* renderer;
Input* input;
float dTime = 0.0f;

void Engine::Run()
{
    Uint64 previousTicks = SDL_GetPerformanceCounter();

    input = new Input();
    game = new Game();
    
    while (SDLisRunning)
    {
        Uint64 ticks = SDL_GetPerformanceCounter();
        Uint64 deltaTicks = ticks - previousTicks;
        previousTicks = ticks; 
        dTime = (float)deltaTicks / SDL_GetPerformanceFrequency();
    
        input->Update();
        if (input->Esc) { SDLisRunning = false; break; }
        
        game->Update();
        
        
        SDL_RenderPresent(renderer);
        // SDL_Delay(16); // Fix deltatime and remove this
    }

    // Destroy game?
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
