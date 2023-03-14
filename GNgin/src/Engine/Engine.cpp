﻿#include "Engine.h"
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
    graphics = new GraphicsSystem();
    graphics->Start;
    drawSystem = new DrawSystem(renderer);
    input = new InputSystem();
    game = new Game();
    entitySystem = new EntitySystem(this);
    game->Start();

    MainLoop();
        
    graphics->Stop;
};

void Engine::MainLoop()
{
    while (isRunning)
    {
        // Clear screen
        graphics->ClearScreen;

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


